from django.conf.urls import url
from . import views
from django.conf import settings
from practicas.views import Nueva_practica
from django.contrib.auth.decorators import login_required


urlpatterns = [
	url(r'^nueva_practica$', views.Nueva_practica, name="nueva_practica"),
	url(r'^detalle/(?P<pk>[0-9]+)/$',views.Detalle_practica.as_view(), name="detalle_practica"),
	url(r'^lista_practicas$', views.Lista_practicas.as_view(), name="lista_practicas"),
	url(r'^modificar/(?P<pk>[0-9]+)/$',login_required(views.Modificar_practica), name="modificar_practica"),
	url(r'^mis_practicas$', login_required(views.Mis_practicas.as_view()), name="mis_practicas"),
	url(r'^eliminar_practica/(?P<pk>[0-9]+)/$',views.Eliminar_practica, name="eliminar_practica"),
]