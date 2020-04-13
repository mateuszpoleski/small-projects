//Poleski Mateusz
package pl.uj.p2;

import pl.uj.p2.uzbrojenie.Bron;
import pl.uj.p2.uzbrojenie.Srebrny;
import pl.uj.p2.uzbrojenie.Stalowy;
import pl.uj.p2.wyjatki.NiedozwolonaKlasa;
import pl.uj.p2.wyjatki.NiedozwolonaRasa;
import pl.uj.p2.wyjatki.NiedozwoloneUzbrojenie;


public class Munchkin implements InterfejsMunchkina {
    
    private Bron bron;
    private Klasa klasa;
    private Rasa rasa;
    private int poziom;

    public Munchkin(int poziom){
        this.poziom = Math.max(0, poziom);
        this.klasa = null;
        this.rasa = null;
        this.bron = null;
    }
    public Munchkin(){
        this.poziom = 1;
        this.klasa = null;
        this.rasa = null;
        this.bron = null;
    }
    @Override
    public void przyjmijKlase(Klasa klasa) throws NiedozwolonaKlasa, NiedozwoloneUzbrojenie {
        if(klasa == null) this.klasa = null;
        else if(this.rasa == null) this.klasa = klasa;
        else if(this.rasa.czyKlasaAkceptowalna(klasa)) this.klasa = klasa;
        else throw new NiedozwolonaKlasa("posiadana klasa pozostaje bez zmian");
        if(this.bron != null && !this.bron.czyMoznaUzbroicMunchkina(this)){
            this.bron = null;
            throw new NiedozwoloneUzbrojenie("");
        }
    }

    @Override
    public void przyjmijRase(Rasa rasa) throws NiedozwolonaRasa, NiedozwoloneUzbrojenie {
        if(rasa == null) this.rasa = null;
        else if(this.klasa == null) this.rasa = rasa;
        else if(this.klasa.czyRasaAkceptowalna(rasa)) this.rasa = rasa;
        else throw new NiedozwolonaRasa("posiadana rasa pozostaje bez zmian");
        if(this.bron != null && !this.bron.czyMoznaUzbroicMunchkina(this)) throw new NiedozwoloneUzbrojenie("");
    }

    @Override
    public void przyjmijBron(Bron bron) throws NiedozwoloneUzbrojenie {
        if(bron==null || bron.czyMoznaUzbroicMunchkina(this)) this.bron=bron;
        else throw new NiedozwoloneUzbrojenie("Munchkin pozostaje uzbrojony we wcześniej posiadaną broń");
    }

    @Override
    public int policzCalkowityPoziom() {
        int calkPzm = 0;
        calkPzm += this.poziom;
        if(this.rasa != null) calkPzm += this.rasa.pobierzPremie();
        if(this.klasa != null) calkPzm += this.klasa.pobierzPremie();
        if(this.bron != null) calkPzm += this.bron.policzPremie(this);
        if(this.rasa != null && this.bron != null && this.rasa.name().equals("Ork") && (this.bron instanceof Stalowy)) calkPzm += 20;
        if(this.klasa != null && this.bron != null && this.klasa.name().equals("Palladyn") && (this.bron instanceof Srebrny)) calkPzm += 25;
        return calkPzm;
    }

    @Override
    public int pobierzSamPoziom() {
        return this.poziom;
    }
    public void zwiekszSamPoziom(int delta){
        int tmpPzm = this.poziom  + delta;
        this.poziom = Math.max(0, tmpPzm);
    }
    public void zmniejszSamPoziom(int delta){
        int tmpPzm = this.poziom  - delta;
        this.poziom = Math.max(0, tmpPzm);
    }

    @Override
    public Klasa pobierzKlasa() {
        return this.klasa;
    }

    @Override
    public Rasa pobierzRasa() {
        return this.rasa;
    }

    @Override
    public Bron pobierzBron() {
        return this.bron;
    }
    
}
