🧠 Memory Scanner for External Process (C++ Builder / VCL)

Bu proje, C++ Builder (VCL) kullanılarak hazırlanmış bir external bellek tarayıcı aracıdır. Belirli bir hedef prosesin belleğinde, kullanıcıdan alınan değerler doğrultusunda veri araması yapar. Kullanıcı, hedef prosesi aktif hale getirerek modül adresi, offset ve karşılaştırılacak değeri belirledikten sonra, uygulama bellek taramasına başlar ve eşleşme bulduğunda kullanıcıyı bilgilendirir.

🎯 Özellikler

✅ Aktif pencereye göre hedef işlemi otomatik algılama

✅ Hedef işlem üzerinde bellek adresi tarama

✅ Modül taban adresi alma (EnumProcessModules, GetModuleFileNameEx)

✅ Çok katmanlı pointer okuma işlemleri (ReadProcessMemory)

✅ Basit kullanıcı arayüzü ile değer arama

✅ Eşleşen adres bulunduğunda kullanıcıyı MessageBoxA ile bilgilendirme

🛠️ Kullanılan Windows API'leri

OpenProcess

EnumProcessModules

GetModuleFileNameEx

GetWindowTextA

GetForegroundWindow

ReadProcessMemory

CreateThread

MessageBoxA

📦 Kullanım Senaryosu

Uygulama çalıştırılır.

Hedef oyun veya uygulama aktif pencere olarak seçilir.

Taban adresin alınacağı modül adı, pointer offsetleri ve aranacak veri kullanıcıdan alınır.

Bellek taraması başlatılır (EtrafOkuBul()).

Aranan değer bellekte bulunduğunda kullanıcıya bildirir.

🧩 Teknik Detaylar

Pointer çözümlemesi için çift ReadLong(...) çağrısı yapılır.

dwGetModuleBaseAddress(...) fonksiyonu ile prosesin istenilen modülünün taban adresi alınır.

Bellekte karşılaştırılacak değer Edit1 üzerinden kullanıcıdan alınır.

Kodun GUI tarafı TForm1 sınıfı üzerinden VCL ile hazırlanmıştır.


⚠️ Uyarılar

Bu uygulama hedef süreç belleğinde işlem yaptığından dolayı yönetici izinleri gerektirebilir.

Kod örneği eğitim ve araştırma amaçlıdır. Yasadışı kullanım kesinlikle önerilmez.

🖥️ Geliştirme Ortamı

IDE: Embarcadero C++ Builder

Dil: Modern C++ (VCL Framework)

Platform: Windows

📄 Lisans

Bu proje açık kaynaklıdır ve MIT lisansı ile lisanslanmıştır. Detaylar için LICENSE dosyasına göz atabilirsiniz.
