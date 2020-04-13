package pl.uj.p2;

import pl.uj.p2.uzbrojenie.Miecz;
import pl.uj.p2.uzbrojenie.StalowyDwurecznyToporZaglady;
import pl.uj.p2.uzbrojenie.WypasionySrebrnyLuk;
import pl.uj.p2.wyjatki.WyjatekMunchkina;


public class Pl {

    
    public static void main(String[] args) {
        Munchkin m = new Munchkin(5);
        m.zmniejszSamPoziom(10);
        System.out.println(m.pobierzSamPoziom());
        System.out.println(m.pobierzKlasa());
        System.out.println(m.pobierzRasa());
        System.out.println(m.pobierzBron());
        System.out.println(m.policzCalkowityPoziom());

        try {
            m.przyjmijRase(Rasa.Gnom);
            m.przyjmijKlase(Klasa.Palladyn);
            m.przyjmijBron(new WypasionySrebrnyLuk());
            System.out.println(m.pobierzRasa());
            System.out.println(m.policzCalkowityPoziom());
            m.przyjmijBron(new StalowyDwurecznyToporZaglady());
            System.out.println(m.policzCalkowityPoziom());
        } catch (WyjatekMunchkina e) {
            System.out.println("Nie można przyjąć rasy Gnoma");
        }

        try {
            m.przyjmijKlase(Klasa.Osilek);
            System.out.println(m.pobierzRasa());
            System.out.println(m.policzCalkowityPoziom());
        } catch (WyjatekMunchkina e) {
            System.out.println("Nie można przyjąć klasy Osiłek");
        }

        try {
            m.przyjmijBron(new StalowyDwurecznyToporZaglady());
            System.out.println(m.pobierzBron() != null);
            System.out.println(m.policzCalkowityPoziom());
        } catch (WyjatekMunchkina e) {
            System.out.println("Nie można uzbroić Munchkina w miecz");
        }

        
    }
    
}
