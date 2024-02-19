<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Sanity Check</title>
    </head>
    <body>
        <h1>Are you sane?</h1>
        <?php
            // Define the correct password
            $correct_pass = "password123";

            // Check if the form is submitted
            if ($_SERVER["REQUEST_METHOD"] == "POST") {
                // make sure password field is set and isn't empty
                if (isset($_POST["password"]) && !empty($_POST["password"])) {
                    // Get the entered password
                    $pass = $_POST["password"];
                    
                    if ($pass === $correct_pass) {
                        // correct pass
                        echo "<p>Correct! The key is: <b>ofthenorth</b></p>";
                    } else {
                        // If the password is incorrect, display an error message
                        echo "<p>Bruh are you a robot or what. Please try again.</p>";
                    }
                }
            } else {
                echo "<p>What is blud trying to do? Please type in a password before submitting.</p>"
            }
        ?>

        <form 
            method="post" 
            action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>"
        >
            <label for="password">What is the password?</label>
            <input type="text" name="password" id="password">
            <input type="submit">
        </form>
    </body>
</html>