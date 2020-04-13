//Mateusz Poleski
package pl.uj.p2;

import pl.uj.p2.uzbrojenie.Bron;
import pl.uj.p2.wyjatki.NiedozwolonaKlasa;
import pl.uj.p2.wyjatki.NiedozwolonaRasa;
import pl.uj.p2.wyjatki.NiedozwoloneUzbrojenie;

public interface InterfejsMunchkina {
    void przyjmijKlase(Klasa klasa) throws NiedozwolonaKlasa, NiedozwoloneUzbrojenie;
    void przyjmijRase(Rasa rasa) throws NiedozwolonaRasa, NiedozwoloneUzbrojenie;
    void przyjmijBron(Bron bron) throws NiedozwoloneUzbrojenie;
    int policzCalkowityPoziom();
    int pobierzSamPoziom();
    Klasa pobierzKlasa();
    Rasa pobierzRasa();
    Bron pobierzBron();
    
}
