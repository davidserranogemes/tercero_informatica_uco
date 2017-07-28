from __future__ import unicode_literals
from django.utils.encoding import python_2_unicode_compatible
from django.db import models
from empresa.models import Empresa
# Create your models here.

@python_2_unicode_compatible
class Curso(models.Model):
	nombre = models.CharField(max_length=50)
	descripcion = models.TextField()
	empresa = models.ForeignKey(Empresa)
	horas = models.PositiveIntegerField()
	inicio= models.DateField()
	final = models.DateField()
	precio = models.PositiveIntegerField()
	zona = models.CharField(max_length=50)
	target = models.TextField()

	def __str__(self):
		return self.nombre