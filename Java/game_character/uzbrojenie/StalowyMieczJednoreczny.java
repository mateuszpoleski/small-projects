//Mateusz Poleski
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;

public class StalowyMieczJednoreczny extends MieczJednoreczny implements Stalowy {
    @Override
    public int policzPremie(InterfejsMunchkina munchkin){
        if( munchkin.pobierzKlasa() == null) return super.policzPremie(munchkin);
        else return super.policzPremie(munchkin) * munchkin.pobierzKlasa().pobierzPremie();
    }
}
