#include <iostream>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

int main() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    if (!ctx) {
        std::cerr << "Failed to create SSL context.\n";
        return 1;
    }

    // Set up SSL connection and load server's certificate (replace "server.crt" with the actual certificate file)
    if (!SSL_CTX_load_verify_locations(ctx, "server.crt", nullptr)) {
        std::cerr << "Failed to load server's certificate.\n";
        SSL_CTX_free(ctx);
        return 1;
    }

    // Create an SSL structure
    SSL* ssl = SSL_new(ctx);

    // Create a BIO structure for the client to connect to the server (replace "localhost:12345" with the actual server address and port)
    BIO* connect_bio = BIO_new_connect("localhost:12345");
    if (!connect_bio) {
        std::cerr << "Failed to create BIO for connecting to the server.\n";
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Connect to the server
    if (BIO_do_connect(connect_bio) <= 0) {
        std::cerr << "Failed to connect to the server.\n";
        BIO_free_all(connect_bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Set up SSL for the connection
    BIO* server_bio = BIO_pop(connect_bio);
    SSL_set_bio(ssl, server_bio, server_bio);

    // Perform the SSL/TLS handshake with the server
    if (SSL_connect(ssl) <= 0) {
        std::cerr << "SSL handshake with the server failed.\n";
        SSL_shutdown(ssl);
        BIO_free_all(connect_bio);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return 1;
    }

    // Communication with the server
    const char* message = "Hello, server!";
    SSL_write(ssl, message, strlen(message));

    char buffer[1024];
    int len = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';
    std::cout << "Received: " << buffer << "\n";

    // Cleanup and exit
    SSL_shutdown(ssl);
    BIO_free_all(connect_bio);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}
