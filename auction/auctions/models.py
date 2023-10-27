from django.contrib.auth.models import AbstractUser
from django.db import models
from django.template.defaultfilters import slugify
import os

class User(AbstractUser):
    watchlist = models.ManyToManyField("Listing", blank=True, related_name="favorites")
    def __str__(self):
        return f"{self.username}"


class Bid(models.Model):
    value = models.IntegerField()
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=True)

    def __str__(self):
        return f"{self.value}"


class Listing(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name="user")
    title = models.CharField(max_length=100)
    description = models.TextField()
    description_small = models.TextField(blank=True, null=True)
    starting_bid = models.IntegerField()
    category = models.CharField(max_length=100, blank=True, null=True)
    current_bid = models.ForeignKey(Bid, models.SET_DEFAULT, default=None, null=True, blank=True)
    active = models.BooleanField(default=True)
    winner = models.ForeignKey(User, on_delete=models.CASCADE, default=None, null=True, related_name="winner", blank=True)
    image = models.ImageField(upload_to="uploads", null=True, blank=True)

    def __str__(self):
        return f"Listing {self.id}: {self.title}"


class Comment(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    text = models.CharField(max_length=500)
    listing = models.ForeignKey(Listing, on_delete=models.CASCADE)

    def __str__(self):
        return self.text