# regex program to take info from football match recap
import re


class GameParser:
    def __init__(self,gospodarze, goscie):
        self.goscie = goscie
        self.gospodarze = gospodarze
        self.naglowek = ""
        self.parsed = False

    def parse(self, napis):
        self.parsed = True
        self.gospodarze.isParsed = True
        self.goscie.isParsed = True
        ###1
        naglowek = re.search("^(.+)\s+v.\s+(.+)\s+(@|at|venue)\s+(.+)\s+on\s+(.+)$", napis, re.I | re.M)
        # wczytuje wyrazy pomiedzy bialymi znakami, w zdaniu ma byc wyraz 'v.' , 'on' itp. grupa(0) to cale zdanie, grupa(3) zawiera laczenie(@|at|venue) - jest tylko pomocnicza.
        gospodarze = naglowek.group(1).strip()
        goscie = naglowek.group(2).strip()
        stadion = naglowek.group(4).strip()
        data = naglowek.group(5).strip()
        ###2
        daneGosp = ""
        daneGosci = ""
        iterator = 0
        pierwszyWyswietlany = re.search("^(lineup)\s+(.*?)$", napis, re.I | re.M)
        lineup = pierwszyWyswietlany.group(1).strip()
        game = re.search("^game$", napis, re.I | re.M)
        game = game.group(0).strip()
        napisOdLineup = napis.partition(lineup)[2]
        napisOdLineup = napisOdLineup.partition(game)[0]
        napisOdGame = napis.partition(game)[2]
        napisOdGame.strip()
        napisOdLineup.strip()
        napisOdLineup = napisOdLineup.replace(lineup, lineup+"1") #  mark
        iluWpisalem = 0;

        czyGospodarzeWyswietlaniNajpierw = pierwszyWyswietlany.group(2) == gospodarze  # bool czy pierwszy klub to godpodarze
        for i in re.finditer("(lineup)*\d+\s+(\D*?)$", napisOdLineup,re.I | re.M):  # wszystkie linie z jedna lub dwoma cyframi, biore tylko imie, po 11 zapisanych zmieniam miejsce zapisu
            if czyGospodarzeWyswietlaniNajpierw and iluWpisalem < 11:
                daneGosp = daneGosp + "\n" + i.group(2).strip()
            elif iluWpisalem < 11:
                daneGosci = daneGosci + "\n" + i.group(2).strip()
            iluWpisalem +=1
            if iluWpisalem == 11 :
                czyGospodarzeWyswietlaniNajpierw = not czyGospodarzeWyswietlaniNajpierw
            if i.group(1) == lineup:
                iluWpisalem = 0

        ###3
        licznikGoliGosp = 0
        licznikGoliGosci = 0
        goleGosp = ""
        goleGosci = ""
        kartkiGosp = ""
        kartkiGosci = ""
        zmianyGosp = ""
        zmianyGosci = ""
        zmienieniZawodnicyGosp = ""
        zmienieniZawodnicyGosci = ""

        # zmiany
        #(\d\d?\+?(\d+)?)
        #^(\d+?)
        for i in re.finditer("(\d\d?\+?(\d+)?)(m|min|')\s+(sub|substitution)\s+(out|off)\s+(.*)\s+(in|on)\s+(.*)", napisOdGame,re.I | re.M):
            # 1-minuty,5-kto,7-na kogo
            tmp = i.group(6)
            tmp = tmp.strip()
            tmp2 = i.group(8)
            tmp2 = tmp2.strip()
            if tmp in daneGosp + zmienieniZawodnicyGosp:
                zmienieniZawodnicyGosp = zmienieniZawodnicyGosp + "\n" + tmp2
                zmianyGosp = zmianyGosp + "\n" + i.group(1) + "' " + tmp2 + " for " + tmp
            else:
                zmienieniZawodnicyGosci = zmienieniZawodnicyGosci + "\n" + tmp2
                zmianyGosci = zmianyGosci + "\n" + i.group(1) + "' " + tmp2 + " for " + tmp
        # kartki
        for i in re.finditer("(\d\d?\+?(\d+)?)(m|min|')\s+card\s+(y|yellow|r|red)\s+(.*)", napisOdGame, re.I | re.M):
            # 1-minuty,3-rodzaj kartki,4-kto dostal
            tmp = i.group(5)
            tmp = tmp.strip()
            kartka = ""
            if i.group(4) == "Y" or i.group(4) == "Yellow":
                kartka = "Y"
            else:
                kartka = "R"
            if tmp in daneGosci + zmienieniZawodnicyGosci:
                kartkiGosci = kartkiGosci + "\n" + i.group(1) + "' " + tmp + " " + kartka
            else:
                kartkiGosp = kartkiGosp + "\n" + i.group(1) + "' " + tmp + " " + kartka
        # gole
        for i in re.finditer("(\d\d?\+?(\d+)?)(m|min|')\s+g+o+a+l+\s+(.*)", napisOdGame, re.I | re.M):
            # 1-minuty,3-kto strzelil
            tmp = i.group(4) # nazwisko strzelca
            czyOG = "og" in tmp or "OG" in tmp
            if czyOG:
                tmp = tmp.replace("(og)", "")
                tmp = tmp.replace("(OG)", "")
            tmp = tmp.strip()
            if czyOG: # bramka samob.
                if tmp in daneGosci+zmienieniZawodnicyGosci: #  z dr.gosci
                    if tmp in goleGosp: #  juz strzelil
                        idx = goleGosp.index(" " + tmp)
                        goleGosp = goleGosp[:idx] + "," + i.group(1) + "'" + goleGosp[idx:]
                        licznikGoliGosp += 1
                    else: #  jeszcze nie strzelil
                        licznikGoliGosp += 1
                        goleGosp = goleGosp + "\n" + i.group(1) + "' " + tmp + " (OG)"
                else:#  z dr.gosp
                    if tmp in goleGosci: #  juz strzelil
                        idx = goleGosci.index(" " + tmp)
                        goleGosci = goleGosci[:idx] + "," + i.group(1) + "'" + goleGosci[idx:]
                        licznikGoliGosci += 1
                    else: #  jeszcze nie strzelil
                        licznikGoliGosci += 1
                        goleGosci = goleGosci + "\n" + i.group(1) + "' " + tmp + " (OG)"
            else:  # zwykla bramka
                if tmp in daneGosci + zmienieniZawodnicyGosci:  # z dr.gosci
                    if tmp in goleGosci: #  juz strzelil
                        idx = goleGosci.index(" " + tmp)
                        goleGosci = goleGosci[:idx] + "," + i.group(1) + "'" + goleGosci[idx:]
                        licznikGoliGosci += 1
                    else: #  jeszcze nie strzelil
                        licznikGoliGosci += 1
                        goleGosci = goleGosci + "\n" + i.group(1) + "' " + tmp
                else:  # z dr.gosp
                    if tmp in goleGosp: #  juz strzelil
                        idx = goleGosp.index(" " + tmp)
                        goleGosp = goleGosp[:idx] + "," + i.group(1) + "'" + goleGosp[idx:]
                        licznikGoliGosp += 1
                    else: #  jeszcze nie strzelil
                        licznikGoliGosp += 1
                        goleGosp = goleGosp + "\n" + i.group(1) + "' " + tmp

        ###
        self.naglowek = "HOME: " + gospodarze + "\n" + \
                        "AWAY: " + goscie + "\n" + \
                        "SCORE: " + str(licznikGoliGosp) + ":" + str(licznikGoliGosci) + "\n" + \
                        "VENUE: " + stadion + "\n" + \
                        "DATE: " + data + "\n"
        #
        self.gospodarze.name = gospodarze
        self.gospodarze.players = daneGosp
        self.gospodarze.cards = kartkiGosp
        self.gospodarze.subs = zmianyGosp
        self.gospodarze.score = licznikGoliGosp
        self.gospodarze.goals = goleGosp
        #
        self.goscie.name = goscie
        self.goscie.players = daneGosci
        self.goscie.cards = kartkiGosci
        self.goscie.subs = zmianyGosci
        self.goscie.score = licznikGoliGosci
        self.goscie.goals = goleGosci

    def print_summary(self):
        if not self.parsed:
            print "NO INFO AVAILABLE!"
        else:
            print self.naglowek
            self.gospodarze.print_summary()
            self.goscie.print_summary()
