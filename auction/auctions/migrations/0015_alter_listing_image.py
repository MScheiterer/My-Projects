# Generated by Django 4.2.5 on 2023-10-18 20:19

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0014_alter_listing_image'),
    ]

    operations = [
        migrations.AlterField(
            model_name='listing',
            name='image',
            field=models.ImageField(default='no-image-available.jpg', upload_to='uploads'),
        ),
    ]