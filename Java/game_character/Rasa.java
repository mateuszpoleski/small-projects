//Mateusz Poleski
package pl.uj.p2;

public enum Rasa {
    Czlowiek(4,new String[]{}),
    Elf(3,new String[]{"Palladyn"}),
    Gnom(5,new String[]{"Osilek"}),
    Krasnolud(2,new String[]{"Szpieg"}),
    Ork(1,new String[]{"Mag","Szpieg"});
    
    private final int premiaDoPoziomu;
    private final String[] nieakceptowalneKlasy;
    
    Rasa(int premia, String[] nieakceptowalneKlasy){
        this.premiaDoPoziomu = premia;
        this.nieakceptowalneKlasy = nieakceptowalneKlasy;
    }
    public boolean czyKlasaAkceptowalna(Klasa klasa){
        for (String i : nieakceptowalneKlasy) {
            if (i.equals(klasa.name())) return false;
        }
        return true;
    }
    public int pobierzPremie(){
        return premiaDoPoziomu;
    }
}
