//Poleski Mateusz
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;
import pl.uj.p2.Rasa;


public class Luk implements Bron {

    @Override
    public boolean czyMoznaUzbroicMunchkina(InterfejsMunchkina munchkin) {
        return munchkin.pobierzRasa() != null && (munchkin.pobierzRasa().equals(Rasa.Elf) || munchkin.pobierzRasa().equals(Rasa.Gnom) );
    }

    @Override
    public int policzPremie(InterfejsMunchkina munchkin) {
        return 3;
    }
    
}
