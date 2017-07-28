from __future__ import unicode_literals
from django.contrib.auth.models import User
from django.db import models

from django.utils.encoding import python_2_unicode_compatible

# Create your models here.



@python_2_unicode_compatible
class Empresa(User):
	telefono=models.CharField(null=False, max_length=9)
	nombre=models.CharField(unique=True, max_length=30)
	descripcion=models.TextField(blank=True)
	def __str__(self):
		return self.nombre