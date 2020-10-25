# ISA_2020
Napište program dns, který bude filtrovat dotazy typu A směřující na domény v rámci dodaného seznamu a jejich poddomény. Ostatní dotazy bude přeposílat v nezměněné podobě specifikovanému resolveru. Odpovědi na dříve přeposlané dotazy bude program předávat původnímu tazateli. Analýza a sestavení DNS zpráv musí být implementována přímo v programu dns. Stačí uvažovat pouze komunikaci pomocí UDP a dotazy typu A. Na jiné typu dotazů a nežádoucí dotazy odpovídejte vhodnou chybovou zprávou.

Při vytváření programu je povoleno použít pouze knihovny pro práci se sokety a další obvyklé funkce používané v síťovém prostředí (jako je netinet/*, sys/*, arpa/* apod.), knihovnu pro práci s vlákny (pthread), signály, časem, stejně jako standardní knihovnu jazyka C (varianty ISO/ANSI i POSIX), C++ a STL. Jiné knihovny nejsou povoleny.

## Spuštění aplikace
Použití: `dns -s server [-p port] -f filter_file`

Pořadí parametrů je libovolné.
### Popis parametrů:
- -s: IP adresa nebo doménové jméno DNS serveru (resolveru), kam se má zaslat dotaz.
- -p port: Číslo portu, na kterém bude program očekávat dotazy. Výchozí je port 53.
- -f filter_file: Jméno souboru obsahující nežádoucí domény.

## Podporované typy dotazů

Uvažujte pouze dotazy typu A, protokol UDP a libovolné protokoly nižších vrstev podporované OS. Není požadována podpora DNSSEC.

## Výstup aplikace

Program nebude vypisovat žádné informace. Volitelně však můžete implementovat parametr -v (verbose), při jehož uvedení bude program vypisovat informace o překladu ve vámi zvoleném formátu.

## Formát souboru se seznamem nežádoucích domén

Nežádoucí domény budou dopředu uloženy v lokálním textovém ASCII souboru, každá doména bude uvedena na samostatném řádku. Prázdné řádky a řádky začínající znakem '#' ignorujte. Uvažujte konce řádků používané v OS GNU/Linux, Microsoft Windows i Apple Mac OS.

### Příklad souborů nežádoucích domén:

- https://dbl.oisd.nl/
- https://pgl.yoyo.org/adservers/serverlist.php?hostformat=nohtml&showintro=1


