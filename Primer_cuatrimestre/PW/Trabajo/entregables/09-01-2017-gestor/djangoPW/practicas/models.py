from __future__ import unicode_literals
from empresa.models import Empresa
from django.db import models
from django.utils.encoding import python_2_unicode_compatible

# Create your models here.

@python_2_unicode_compatible
class Practica(models.Model):
	nombre = models.CharField(max_length=50)
	descripcion= models.TextField()
	empresa = models.ForeignKey(Empresa)
	remuneracion = models.PositiveIntegerField()
	horas_semana = models.PositiveIntegerField()
	dias_trabajo = models.PositiveIntegerField()
	zona = models.CharField(max_length=50)
	target= models.TextField()
	duracion = models.PositiveIntegerField()

	def __str__(self):
		return self.nombre