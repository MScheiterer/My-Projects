from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("listings", views.active_listings, name="active_listings"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("add", views.create_listing, name="create_listing"),
    path("listings/<int:listing_id>", views.listing_view, name="listing"),
    path("watchlist", views.watchlist_view, name="watchlist"),
    path("watchlist/add/<int:listing_id>", views.watchlist_add, name="watchlist_add"),
    path("watchlist/remove/<int:listing_id>", views.watchlist_remove, name="watchlist_remove"),
    path("categories", views.categories_view, name="categories"),
    path("listings/<str:category>", views.category_listings_view, name="listings_in_category"),
    path("listings/<int:listing_id>/comment", views.add_comment, name="add_comment"),
    path("listing/<int:listing_id>/place_bid", views.place_bid, name="place_bid"),
    path("listing/<int:listing_id>/close", views.close_listing, name="close_listing"),
]