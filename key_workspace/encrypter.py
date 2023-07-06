from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import serialization
import sys

# RSA key parameters
modulus = 221
public_exponent = 5
private_exponent = 77
prime1 = 13
prime2 = 17
exponent1 = 5
exponent2 = 13
coefficient = 10

# Construct the RSA private key object
private_key_numbers = rsa.RSAPrivateNumbers(
    p=prime1,
    q=prime2,
    d=private_exponent,
    dmp1=exponent1,
    dmq1=exponent2,
    iqmp=coefficient,
    public_numbers=rsa.RSAPublicNumbers(e=public_exponent, n=modulus)
)

private_key = private_key_numbers.private_key()

# print(private_key.private_numbers())
# print(private_key.public_key())

# Example usage: Encrypting a message
plaintext = 'g'
print(sys.getsizeof(plaintext))
# ciphertext = private_key.public_key().encrypt(
#     plaintext,
#     padding=padding.PKCS1v15()
# )

#Print the ciphertext
# print(ciphertext.hex())
