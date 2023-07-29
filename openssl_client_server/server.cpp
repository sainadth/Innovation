#include <iostream>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

int main() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(SSLv23_server_method());
    if (!ctx) {
        std::cerr << "Failed to create SSL context.\n";
        return 1;
    }

    // Load the server's certificate and private key (replace "server.crt" and "server.key" with the actual files)
    if (!SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) ||
        !SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) ||
        !SSL_CTX_check_private_key(ctx)) {
        std::cerr << "Failed to load server's certificate or private key.\n";
        SSL_CTX_free(ctx);
        return 1;
    }

    // Create an SSL structure for the server
    SSL* ssl = SSL_new(ctx);

    // Create a BIO structure for the server to listen on a specific port (replace "12345" with the desired server port)
    BIO* accept_bio = BIO_new_accept("12345");
    if (!accept_bio) {
        std::cerr << "Failed to create BIO for accepting connections.\n";
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Bind and listen to the server port
    if (BIO_do_accept(accept_bio) <= 0) {
        std::cerr << "Failed to bind and listen to the server port.\n";
        BIO_free_all(accept_bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Accept a new connection and set up SSL for the accepted connection
    if (BIO_do_accept(accept_bio) <= 0) {
        std::cerr << "Failed to accept a new connection.\n";
        BIO_free_all(accept_bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    BIO* client_bio = BIO_pop(accept_bio);
    SSL_set_bio(ssl, client_bio, client_bio);

    // Perform the SSL/TLS handshake with the client
    if (SSL_accept(ssl) <= 0) {
        std::cerr << "SSL handshake with the client failed.\n";
        SSL_shutdown(ssl);
        BIO_free_all(accept_bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Communication with the client
    char buffer[1024];
    int len = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    std::cout << "Received: " << buffer << "\n";

    const char* message = "Hello, client!";
    SSL_write(ssl, message, strlen(message));

    // Cleanup and exit
    SSL_shutdown(ssl);
    BIO_free_all(accept_bio);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}
