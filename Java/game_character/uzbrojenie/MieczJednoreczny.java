//Mateusz Poleski
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;

public class MieczJednoreczny extends Miecz {
    @Override
    public int policzPremie(InterfejsMunchkina munchkin){
        if( munchkin.pobierzRasa() == null) return super.policzPremie(munchkin);
        else return super.policzPremie(munchkin) * munchkin.pobierzRasa().pobierzPremie();
    }
}
