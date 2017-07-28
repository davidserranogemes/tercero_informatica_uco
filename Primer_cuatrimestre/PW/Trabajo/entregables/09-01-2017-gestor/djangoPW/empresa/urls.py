from django.conf.urls import url
from . import views
from django.conf import settings
from django.contrib.auth.decorators import login_required

urlpatterns = [
	url(r'^registro$',views.Registro,name="registro"),
	url(r'^agregado$',views.Agregado,name="agreagado"),
	url(r'^login$',views.Login, name="login"),
	url(r'^logout$',views.Logout, name="logout"),
	url(r'^already_loged$',views.Already_loged, name="already_loged"),
	url(r'^not_loged$',views.Not_loged, name="not_loged"),
	url(r'^mi_empresa$',views.Mi_empresa, name='mi_empresa'),
	url(r'^detalle/(?P<pk>[0-9]+)/$', views.Detalle_empresa, name="detalle_empresa"),
	url(r'^modificar_mi_empresa$',views.Modificar_mi_empresa, name="modificar_mi_empresa"),
	url(r'^modificar_mi_contrasenia$',views.Cambiar_contrasenia, name="modificar_mi_contrasenia"),
]