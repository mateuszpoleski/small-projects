//Poleski Mateusz
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;
import pl.uj.p2.Klasa;
import pl.uj.p2.Rasa;

public class StalowyDwurecznyToporZaglady extends Topor implements Stalowy {
    @Override
    public boolean czyMoznaUzbroicMunchkina(InterfejsMunchkina munchkin) {
        if(munchkin.pobierzKlasa()!=null && munchkin.pobierzKlasa().equals(Klasa.Osilek) ) return true;
        if(munchkin.pobierzRasa()!=null && munchkin.pobierzRasa().equals(Rasa.Ork)) return true;
        return false;
    }

    @Override
    public int policzPremie(InterfejsMunchkina munchkin) {
        return super.policzPremie(munchkin) * munchkin.pobierzSamPoziom();
    }
}
