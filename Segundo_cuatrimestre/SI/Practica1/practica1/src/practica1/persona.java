/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;

/**
 *
 * @author hidesagred
 */
public class persona {
    private String _nombre;
    private String _apellidos;
    private int _edad;
    
    public persona(String nombre, String apellidos, int edad){
        _nombre=nombre;
        _apellidos=apellidos;
        _edad=edad;
    }
    
    public void setNombre(String nombre){
        _nombre=nombre;
    }
    public void setApellidos(String apellidos){
        _apellidos=apellidos;
    }
    public void setEdad(int edad){
        assert(edad>=0);
        _edad=edad;
    }
    
    public String getNombre(){
        return _nombre;
    }
    public String getApellidos(){
        return _apellidos;
    }
    public int getEdad(){
        return _edad;
    }
            
}
