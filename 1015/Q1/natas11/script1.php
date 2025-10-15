<?php

$plaintext = json_encode(array("showpassword" => "no", "bgcolor" => "#ffffff"));
$ciphertext = base64_decode("HmYkBwozJw4WNyAAFyB1VUcqOE1JZjUIBis7ABdmbU1GIjEJAyIxTRg=");

$outText = "";

for ($i = 0; $i < strlen($plaintext); $i++) {
    $outText .= $plaintext[$i] ^ $ciphertext[$i % strlen($ciphertext)];
}

print $outText;
?>