//Poleski Mateusz
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;
import pl.uj.p2.Klasa;



public class Topor implements Bron {

    @Override
    public boolean czyMoznaUzbroicMunchkina(InterfejsMunchkina munchkin) {
        return munchkin.pobierzKlasa()==null || (!munchkin.pobierzKlasa().equals(Klasa.Szpieg) );
    }

    @Override
    public int policzPremie(InterfejsMunchkina munchkin) {
        if (munchkin.pobierzKlasa() == null || !munchkin.pobierzKlasa().equals(Klasa.Osilek)) return 5;
        else return 10;
    }
    
}
