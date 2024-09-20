#import QR code libraby
import qrcode

#Function converts URL to QR
img = qrcode.make("https://www.example.com")

#Function saves generated QR to a PNG with the name "qr.png"
img.save("qr.png" , "PNG")
