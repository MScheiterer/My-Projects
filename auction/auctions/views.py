from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, redirect
from django.urls import reverse
from django import forms
from .models import User, Listing, Comment, Bid

class ListingForm(forms.Form):
    title = forms.CharField(max_length=100, label="Title")
    description = forms.CharField(label="Description",widget=forms.Textarea)
    category = forms.CharField(label="Category", max_length=100, required=False)
    starting_bid = forms.FloatField(label="Starting Bid")
    image = forms.ImageField(label="(Optional) Image:", required=False)

class CommentForm(forms.Form):
    text = forms.CharField(max_length=500, label="")

class BiddingForm(forms.Form):
    value = forms.IntegerField(min_value=0, label="")

def index(request):
    return render(request, "auctions/index.html")

def active_listings(request):
    return render(request, "auctions/listings.html", {"listings": Listing.objects.all()})


def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")

@login_required
def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "auctions/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "auctions/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")

@login_required
def create_listing(request):
    if request.method == "POST":
        form = ListingForm(request.POST, request.FILES)
        if form.is_valid():
            user = User.objects.get(id=request.user.id)
            title = form.cleaned_data["title"]
            description = form.cleaned_data["description"]
            category = form.cleaned_data["category"]
            starting_bid = form.cleaned_data["starting_bid"]
            image = form.cleaned_data["image"]
            if len(description) > 100:
                description_small = description[:100] + "..."
            else:
                description_small = description
            listing = Listing(title=title, description=description, description_small=description_small, starting_bid=starting_bid, 
                            category=category, user=user, image=image)
            listing.save()
            return HttpResponseRedirect(reverse("active_listings"))
        else:
            return HttpResponse("Something went wrong...")
    else:
        listing_form = ListingForm()
        return render(request, "auctions/create_new_listing.html", {"listing_form": listing_form})
    

def listing_view(request, listing_id):
    listing = Listing.objects.get(pk=listing_id)
    user = User.objects.get(id=request.user.id)
    watchlist = user.watchlist.all()
    watchlisted = False
    if listing in watchlist:
        watchlisted = True
    all_comments = Comment.objects.all()
    comments = []
    for comment in all_comments:
        if comment.listing.id == listing_id:
            comments.append(comment)
    context = {"listing": listing, "watchlisted": watchlisted, 
            "comments": comments, "comment_form": CommentForm(),
            "bidding_form": BiddingForm()}
    return render(request, "auctions/listing.html", context)

@login_required
def watchlist_view(request):
    user = User.objects.get(id=request.user.id)
    listings = user.watchlist.all()
    return render(request, "auctions/watchlist.html", {"listings": listings})

@login_required
def watchlist_add(request, listing_id):
    listing = Listing.objects.get(id=listing_id)
    user = User.objects.get(id=request.user.id)
    user.watchlist.add(listing)
    return redirect("listing", listing_id=listing_id)

@login_required
def watchlist_remove(request, listing_id):
    listing = Listing.objects.get(id=listing_id)
    user = User.objects.get(id=request.user.id)
    user.watchlist.remove(listing)
    return redirect("listing", listing_id)
    
def categories_view(request):
    listings = Listing.objects.all()
    categories = []
    for listing in listings:
        if listing.category != "" and listing.category not in categories:
            categories.append(listing.category)
    return render(request, "auctions/categories.html", {"categories": categories})

def category_listings_view(request, category):
    listings = Listing.objects.filter(category=category)
    return render(request, "auctions/listings_in_category.html", {"listings": listings, "category": category})

@login_required
def add_comment(request, listing_id):
    if request.method == "POST":
        user = User.objects.get(id=request.user.id)
        listing = Listing.objects.get(id=listing_id)
        form = CommentForm(request.POST)
        if form.is_valid():
            text = form.cleaned_data["text"]
            comment = Comment(user=user, listing=listing, text=text)
            comment.save()
            return redirect("listing", listing_id)

@login_required
def place_bid(request, listing_id):
    if request.method == "POST":
        user = User.objects.get(id=request.user.id)
        listing = Listing.objects.get(id=listing_id)
        form = BiddingForm(request.POST)
        if form.is_valid():
            value = form.cleaned_data["value"]
            if (listing.current_bid and value > listing.current_bid.value) or (not listing.current_bid and value > listing.starting_bid):
                bid = Bid(user=user, listing=listing, value=value)
                bid.save()
                listing.current_bid = bid
                listing.save()
                return redirect("listing", listing_id)
            else: # Bid not higher than last bid
                return HttpResponse("Bidding value not high enough!")

@login_required
def close_listing(request, listing_id):
    listing = Listing.objects.get(id=listing_id)
    if listing.current_bid:
        user = User.objects.get(id=listing.current_bid.user.id)
        listing.winner = user
    listing.active = False
    listing.save()
    return redirect("listing", listing_id)
