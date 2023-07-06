from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric.rsa import RSAPublicNumbers

# Prime numbers p and q
p = 123456789
q = 987654321

# Generate RSA key
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048,
)

# Calculate modulus n
n = p * q

# Set the prime numbers manually
public_numbers = RSAPublicNumbers(e=65537, n=n)
private_numbers = private_key.private_numbers()
d = private_numbers.d
dp = private_numbers.dmp1
dq = private_numbers.dmq1
iqmp = private_numbers.iqmp

# Calculate private exponent using the prime numbers
private_exponent = rsa.rsa_crt_dmp1(d, p)
private_exponent = rsa.rsa_crt_dmq1(private_exponent, q)
private_exponent = rsa.rsa_crt_iqmp(private_exponent, p)

# Create a new private key using the provided prime numbers
new_private_key = rsa.RSAPrivateNumbers(
    p=p,
    q=q,
    d=private_exponent,
    dmp1=dp,
    dmq1=dq,
    iqmp=iqmp,
    public_numbers=public_numbers
).private_key()

# Export private key to PEM format
private_key_pem = new_private_key.private_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PrivateFormat.PKCS8,
    encryption_algorithm=serialization.NoEncryption()
)

# Save private key to file
with open("private_key.pem", "wb") as f:
    f.write(private_key_pem)
