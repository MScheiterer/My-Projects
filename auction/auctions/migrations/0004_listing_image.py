# Generated by Django 4.2.6 on 2023-10-09 15:09

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0003_alter_listing_winner'),
    ]

    operations = [
        migrations.AddField(
            model_name='listing',
            name='image',
            field=models.ImageField(null=True, upload_to=''),
        ),
    ]
