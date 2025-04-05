#!/bin/bash

# Mise à jour des paquets existants
sudo apt update && sudo apt upgrade -y

# Installation des outils nécessaires
sudo apt install -y dnsmasq hostapd php php-cli php-fpm php-mysql apache2 phpmyadmin nodejs npm

# Activation des services hostapd et dnsmasq
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq

# Configuration du hotspot

# Modifier la configuration réseau
echo "interface wlan0" | sudo tee -a /etc/dhcpcd.conf
echo "static ip_address=192.168.220.1/24" | sudo tee -a /etc/dhcpcd.conf
echo "nohook wpa_supplicant" | sudo tee -a /etc/dhcpcd.conf

# Redémarrer le service dhcpcd pour appliquer les changements
sudo systemctl restart dhcpcd

# Configuration de hostapd pour activer le WiFi hotspot
cat <<EOL | sudo tee /etc/hostapd/hostapd.conf
interface=wlan0
driver=nl80211
ssid=Distributeur
hw_mode=g
channel=6
auth_algs=1
wpa=2
wpa_passphrase=raspberry
EOL

# Modifier le fichier de configuration principal de hostapd pour pointer vers le fichier conf
sudo sed -i 's|#DAEMON_CONF=""|DAEMON_CONF="/etc/hostapd/hostapd.conf"|' /etc/default/hostapd

# Configurer dnsmasq pour fournir une adresse IP aux clients connectés
cat <<EOL | sudo tee /etc/dnsmasq.conf
interface=wlan0
dhcp-range=192.168.220.50,192.168.220.150,255.255.255.0,24h
EOL

# Redémarrer dnsmasq et hostapd
sudo systemctl restart dnsmasq
sudo systemctl restart hostapd

# Installation de PHPMyAdmin
# Configurer Apache pour utiliser PHPMyAdmin
sudo ln -s /usr/share/phpmyadmin /var/www/html/phpmyadmin
sudo systemctl restart apache2

# Installation de Node.js et NPM
curl -sL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs

# Vérifier que Node.js est bien installé
node -v
npm -v

# Indication que l'installation est terminée
echo "L'installation est terminée. Le hotspot est activé, PHP, phpMyAdmin et Node.js sont installés."