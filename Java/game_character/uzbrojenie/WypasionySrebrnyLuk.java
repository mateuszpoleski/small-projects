//Poleski Mateusz
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;
import pl.uj.p2.Klasa;

public class WypasionySrebrnyLuk extends Luk implements Srebrny {
    @Override
    public boolean czyMoznaUzbroicMunchkina(InterfejsMunchkina munchkin) {
        if(munchkin.pobierzKlasa() == null) return super.czyMoznaUzbroicMunchkina(munchkin);
        else return super.czyMoznaUzbroicMunchkina(munchkin) && !(munchkin.pobierzKlasa().equals(Klasa.Len) || munchkin.pobierzKlasa().equals(Klasa.Osilek) );
    }

    @Override
    public int policzPremie(InterfejsMunchkina munchkin) {
        if( munchkin.pobierzRasa() == null) return super.policzPremie(munchkin);
        else return munchkin.pobierzRasa().pobierzPremie()*super.policzPremie(munchkin);
    }
}
