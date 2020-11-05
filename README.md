# DNS resolver – projekt ISA 2020
Program DNS filtruje dotazy typu A směřující na domény v rámci dodaného seznamu a na jejich poddomény. Ostatní dotazy program přeposílá v nezměměné podobě specifikovanému resolveru. Odpovědina přeposlané dotazy program předává původnímu tazateli. 
Program DNS podporuje pouze komunikaci UDP a dotazy typu A. Na jiné typy dotazů je odpovídáno chybovou zprávou.

## Spuštění aplikace
Použití: `dns -s server [-p port] -f filter_file -v`

Pořadí parametrů je libovolné.
### Popis parametrů
- `-s server`: IP adresa nebo doménové jméno DNS serveru (resolveru), kam se má zaslat dotaz.
- `-p port`: Číslo portu, na kterém bude program očekávat dotazy. Výchozí je port 53.
- `-f filter_file`: Jméno souboru obsahující nežádoucí domény.
- `-v`: přepínač zapínající mód, v němž program vypisuje informace o překladu.

V případě, že je číslo portu neplatné, pak je využit výchozí port 53. Neplatné parametry jsou při vyhodnocování přeskočeny.

## Limity
Program podporuje pouze komunikaci pomocí protokolu UDP a dotazy typu A. Na jiné typy dotazů je odpovídání chybovou zprávou. Aplikace nepodporuje DNSSEC.

## Formát souboru se seznamem nežádoucích domén
Nežádoucí domény musí být dopředu uloženy v lokálním textovém ASCII souboru. Každá doména určena k vyfiltrování musí být uvedena na samostatném řádku. Prázdné řádky a řádky začínající znakem '#' jsou ignorovány. Ignorovány jsou taktéž bílé znaky na začátku a konci řádku.

## Soubory
Složka `src` obsahuje zdrojové soubory, které je možné přeložit pomocí utility `make`. Podrobnější informace je možné nalézt v souboru `manual.pdf`.
