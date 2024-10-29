# SSL Certificate and Secure Server Setup

## Overview
This project demonstrates the process of setting up a secure web server with SSL/TLS encryption using **OpenSSL**, **Apache**, and a self-signed certificate. The setup includes generating public and private key pairs, creating a Certificate Signing Request (CSR), and configuring Apache to serve a site over HTTPS.

Through this project, I gained foundational skills in SSL/TLS encryption and the steps needed to establish a secure connection between a client and a server.

---

## Key Steps and Commands

### 1. Install Apache Web Server
Verified the Apache installation and configured it as our web server for HTTPS.

```bash
sudo apt install apache2
```
### 2. Configure SSL Folder and Remove Existing Keys
Ensured the directory /etc/apache2/ssl exists and removed any existing SSL files to start fresh.

```bash
sudo mkdir -p /etc/apache2/ssl
cd /etc/apache2/ssl
sudo rm *
```
### 3. Generate Private Key and CSR
Generated a private key and a Certificate Signing Request (CSR) for our server.
```bash
sudo openssl genrsa -des3 -out server.key 2048
sudo openssl req -new -key server.key -out server.csr
```
### 4. Create Self-Signed Certificate
Signed the CSR with our own private key to create a self-signed certificate valid for 365 days.
```bash
sudo openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt
```
### 5. Enable SSL Module in Apache
Enabled SSL in Apache and restarted the server to apply changes.
```bash
sudo a2enmod ssl
sudo systemctl restart apache2
```
### 6. Configure Virtual Host for HTTPS
Created a new virtual host configuration for www.testpage.net to serve the site over HTTPS.
```bash
sudo a2enmod ssl
sudo systemctl restart apache2
```
##### 1. Copied the default config file and modified it:
```bash
sudo cp /etc/apache2/sites-available/000-default.conf /etc/apache2/sites-available/www.testpage.net.conf
```
##### 2. Edited `/etc/apache2/sites-available/www.testpage.net.conf` to:
* Set VirtualHost *:443 for HTTPS
* Add ServerName www.testpage.net
* Set DocumentRoot /var/www/testpage
* Specify the paths to server.crt and server.key for SSL
##### 3. Enabled the site and updated `/etc/hosts`:
```bash
sudo a2ensite www.testpage.net
sudo systemctl restart apache2
```
### 7. Verify SSL Connection
Opened `https://www.testpage.net` in the browser, accepted the self-signed certificate, and confirmed the secure connection.

## Skills and Knowledge Gained
* SSL/TLS Basics: Understanding the role of SSL certificates in securing network communications.
* Certificate Management: Learned to create, sign, and configure SSL certificates using OpenSSL.
* Apache Configuration: Configured Apache for HTTPS and created a virtual host for SSL-based connections.
* Self-Signed Certificates: Recognized the importance and limitations of self-signed certificates for testing.
