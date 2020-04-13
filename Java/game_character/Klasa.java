//Mateusz Poleski
package pl.uj.p2;

public enum Klasa {
    Len(-1,new String[]{}),
    Mag(4,new String[]{"Ork","Gnom"}),
    Osilek(5,new String[]{"Gnom"}),
    Palladyn(2,new String[]{"Elf"}),
    Szpieg(2,new String[]{"Ork","Krasnolud"});
    
    private final int premiaDoPoziomu;
    private final String[] nieakceptowalneRasy;
    
    Klasa(int premia, String[] nieakceptowalneRasy){
        this.premiaDoPoziomu = premia;
        this.nieakceptowalneRasy = nieakceptowalneRasy;
    }
    public boolean czyRasaAkceptowalna(Rasa rasa){
        for (String i : nieakceptowalneRasy) {
            if (i.equals(rasa.name())) return false;
        }
        return true;
    }
    public int pobierzPremie(){
        return premiaDoPoziomu;
    }
}
