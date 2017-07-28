/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1.factorial;

/**
 *
 * @author hidesagred
 */
public class factorial {
    
    public double CalculaFactorial(double factor){
        assert(factor>=0);
        if(factor==1 || factor==0){
            return 1;
        }else{
            return CalculaFactorial(factor-1) * factor;
        }
    }
}
