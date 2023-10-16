
# Model Lighting for Plastic or Diecast models.

You can make lighting for your plastic or diecast models.

Arduino project files, KiCad PCB design files are in this project.

If you don't want to use reed relays, you can replace reed relay with pullup buttons, or pullup short circuits. If you choose pullup buttons or pullup shortcircuits, you need use codes in "without-reed-relays" branch.

P.S.: Please, test circuit on breadboard before make/create final circuit.

### Complete component list is below.

- 1 x Arduino Uno
- 1 x Extra AT Mega 328 P Series Chip
- 12 x White LED (if neccessary for project you can use warm white led.)
- 4 x Red LED
- 4 x Yellow LED
- 10 x 470 ohm SMD Resistor (You can use 330 ohm.)
- 1 x Push Button
- 5 x Magnetic Reed Relay
- 5 x Neodium Magnet (I have used 3mm disc.)
- 2 x 22pF Capasitor
- 1 x 16.000 MHz Crystal
- 1 x 1838B IR Receiver
- 1 x 38KHz IR Remote Controller

### IR Remote Controller Button Functions

- OK => System on/off
- 1 => Parking lights on/off
- 2 => Dipped beam on/off
- 3 => High beam on/off
- 4 => Left turn signal on/off
- 5 => Right turn signal on/off
- 6 => Brake ligth on/off
- 7 => Hazard warning ligths on/off
- 8 => Reverse light on/off


# Plastik yada Diecast Modeller İçin Aydınlatma.

Bu projeyi kullanarak plastik yada diecast modellerinize uzaktan kumanda kontrollü ışıklandırma yapabilirsiniz.

Arduino proje dosyaları ve KiCad baskı devre tasarım dosyaları dahildir.

Eğer reed röleler yerine pullup button yada pullup kısa devre yapmak isterseniz, "without-reed-relays" branchi içerisindeki kodları kullanmanız gerekmektedir.

NOT: Lütfen devrenin baskı halini yapmadan önce breadboard üzerinde testlerinizi yapın.

### Komponent Listesi

- 1 x Arduino Uno
- 1 x Ekstra AT Mega 328 P Serisi Entegre Çip
- 12 x Beyaz LED (Projenize göre gün ışığı led de olabilir.)
- 4 x Kırmızı LED
- 4 x Sarı LED
- 10 x 470 ohm SMD Direnç (330 ohm da kullanılabilir.)
- 1 x Push Button
- 5 x Magnetic Reed Röle
- 5 x Neodium Mıknatıs (Ben 3mm yuvarlak olanlardan kullandım.)
- 2 x 22pF Kondansatör
- 1 x 16.000 MHz Kristal
- 1 x 1838B IR Alıcı
- 1 x 38KHz IR Uzaktan Kumanda

### IR Uzaktan Kumanda DÜğme Fonksiyonları

- OK => Sistem aç/kapat
- 1 => Parklar aç/kapat
- 2 => Kısalar aç/kapat
- 3 => Uzunlar aç/kapat
- 4 => Sol sinyal aç/kapat
- 5 => Sağ sinyal aç/kapat
- 6 => Fren lambası aç/kapat
- 7 => Dörtlüler aç/kapat
- 8 => Geri vites lambası aç/kapat
- Sol Ok => Sol sinyal aç/kapat
- Sağ Ok => Sağ sinyal aç/kapat
