# Hayatta Kalma Simülatörü (C Programı)

Bu proje, temel C programlama yapıları (if-else, switch-case, for, do-while, fonksiyonlar, rastgele sayı üretimi) kullanılarak hazırlanmış bir **hayatta kalma simülasyonu**dur. Amaç, sağlık, enerji ve yemek durumunu yöneterek olabildiğince uzun süre hayatta kalmaktır.

---

## 🎮 Oyun Mantığı

Oyuncu çeşitli komutlar girerek karakterini yönetir. Her komut sağlık, enerji, yemek veya sığınak durumunu etkiler. Rastgele olaylar, tehlike dalgaları ve kilit açma sistemi oyun içinde çeşitlilik sağlar.

Başlangıç değerleri:
- Sağlık: 100
- Enerji: 100
- Yemek: 5
- Sığınak: Yok

---

## 🧩 Kullanılan Programlama Yapıları

Bu projede ders kapsamında istenen tüm yapılar bulunmaktadır:

- **Fonksiyonlar**
- **Switch-case** (komut kontrolü)
- **If–Else** (durumsal kararlar)
- **For döngüsü** (tehlike serisi)
- **Do–While döngüsü** (şifreli ilerleme)
- **Aritmetik ve mantıksal operatörler**
- **Rastgele sayı üretimi** (`rand()`, `srand()`, `time()`)

---

## 🔠 Komutlar

| Komut | Açıklama |
|-------|----------|
| **A** | Avlan → Enerji harcar, yemek bulma şansı vardır |
| **S** | Sığınak arama → Mantıksal operatörler ile başarı şansı |
| **E** | Envanter görüntüleme |
| **R** | Dinlenme → Sağlık ve enerji yenilenir |
| **F** | Tehlike Serisi → FOR döngüsü ile ardışık riskler |
| **P** | Şifreli İlerleme → DO-WHILE ile kilit açma sistemi |
| **X** | Oyundan çıkış |

---

## ⚠ Oyun Mekanikleri

### 🔸 Avlanma (A)
- 10 enerji harcanır.
- Yemek bulma şansı enerji ve şansa bağlı.
- Yemek bulunduğunda enerji kazanımı mümkündür.

### 🔸 Sığınak Arama (S)
- Mantıksal koşullara göre başarı:
  - Yemek ≥ 2 VE enerji ≥ 40  
  - **VEYA** büyük bir şans (sans > 85)
- Başarısızlık durumunda küçük yaralanma olabilir.

### 🔸 Dinlenme (R)
- Yemek varsa daha verimli dinlenilir.
- Sağlık ve enerji artar.

### 🔸 Tehlike Serisi (F)
- 3–5 arası tehlike ardışık olarak FOR döngüsüyle uygulanır.
- Sığınak varsa hasar azalır.

### 🔸 Şifreli İlerleme (P)
- DO-WHILE döngüsü ile kilit açılmaya çalışılır.
- Her deneme enerji azaltır.
- “X” ile vazgeçilebilir.

---

## 🧪 Öldü mü Kontrolü

Her komut sonrası:
- Sağlık ≤ 0  
- Enerji ≤ 0  

ise oyun otomatik olarak biter.

---

## ▶ Programı Çalıştırma

```bash
gcc hayatta_kalma.c -o hayatta
./hayatta
