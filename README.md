# LCD 48x84
<h2>PCD8544 Driver</h2>

<p>LCD Driver pcd8544 for AVR Atmega16</p>
<p>C library for driving LCD display Nokia 5110 with driver pcd8544 through SPI's Atmega16</p>

<h2>Demonstration</h2>
<img src="pcd8544.jpg" />

<h3 style="text-align:justify">Teória radiča&nbsp;displeja&nbsp;Nokia 5110</h3>

<p style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">PCD8544 je nízkoenergetický CMOS LCD kontrolér/driver navrhnútý na riadenie grafického displeja so 48 riadkami a 84 stĺpcami. S mikrokontrolérom pracuje prostredníctvom sériového rozhania. Charakteristické parametre PCD8544:</span></span></p>

<ul>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">48 riadkov, 84 stĺpcov&nbsp;</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">pamäť displeja 48 x 84 bitov (</span></span><span style="font-family:verdana,geneva,sans-serif; font-size:12px">RAM)</span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">sériová komunikácia do 4 Mbits/s</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">externý resetovací vstupný pin</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">multiplexný pomer 48</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">napájacie napätie v rozmedzí 2,7 až 3,3 V</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">napájacie napätie displeja 6,0 až 8,5 V pre interné napájanie a 6 až 9 V pre externé napájanie</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">nizkonenergetické prevedenie vhodné pre napájanie batériou</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">tepelná kompenzácia</span></span></li>
	<li style="text-align:justify"><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif">rozsah teplôt okolia -25 až +70 °C</span></span></li>
</ul>

<p><a href="/Public/images/atmel/atmega8/pcd8544/nokia-lcd-back.jpg" target="_blank"><img alt="Predná strana lcd displeja Nokia 5110 s radičom pcd8544" src="/Public/images/atmel/atmega8/pcd8544/nokia-lcd-front.jpg" style="height:400px; width:400px" /><img alt="Zadná strana lcd displeja Nokia 5110 s radičom pcd8544" src="/Public/images/atmel/atmega8/pcd8544/nokia-lcd-back.jpg" style="height:400px; width:400px" /></a><br />
<span style="font-size:11px"><strong><span style="font-family:arial,helvetica,sans-serif">Obr. 1 - LCD displej z Nokie 5110 s radičom pcd8544</span></strong></span></p>

<p style="text-align:justify"><span style="font-family:verdana,geneva,sans-serif"><span style="font-size:12px">V článku bude&nbsp;načrtnútý&nbsp;príklad&nbsp;prepojenia a komunikácie lcd displeja s&nbsp;miktrokontrolérom rady Atmega8 / Atmega16 u ktorých je využitá SPI&nbsp;komunikácia&nbsp;(MOSI, SCK, SS). Signál MISO nie je využitý, keďže sa jedna iba o jednosmerný prenos dát - z mikrokontroléra do ovládača displeja.</span></span></p>

<h4>Označenie a význam portov</h4>

<ul>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>RST</strong> (RESET) - externý&nbsp;resetovací impulz&nbsp;(aktívna úroveň log. 0). Trvanie impulzu by nemalo byť menej ako 100 ns.</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>CE</strong> (CHIP ENABLED) - povoľuje činnosť s radičom / kontrolérom (aktívna úroveň log. 0).</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>DC</strong> (DATA COMMAND) - definuje typ príjmaných dát (dáta - log. 1 /&nbsp;príkaz - log. 0).</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>DIN </strong>(DATA INPUT)<strong>&nbsp;</strong>- vstupný port pre dáta / príkaz.</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>CLK</strong>&nbsp;(CLOCK) - hodinový impulz.</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>UCC</strong>&nbsp;- napájacie napätie 2,7 až 3,3 V.</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>LIGHT</strong>&nbsp;- nastavenie kontrastu (v obvyklom prípade&nbsp;uzemnené).</span></span></li>
	<li><span style="font-size:12px"><span style="font-family:verdana,geneva,sans-serif"><strong>GND</strong>&nbsp;- uzemnenie.</span></span></li>
</ul>

<h2>Inspiration & Acknowledgement</h2>
https://github.com/mvadai/muonhunter/blob/master/avr/
