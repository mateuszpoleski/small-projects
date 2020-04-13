//Poleski Mateusz
package pl.uj.p2.uzbrojenie;

import pl.uj.p2.InterfejsMunchkina;


public class Miecz implements Bron {

    @Override
    public boolean czyMoznaUzbroicMunchkina(InterfejsMunchkina munchkin) {
        return true;
    }

    @Override
    public int policzPremie(InterfejsMunchkina munchkin) {
        return 2;
    }
    
}
