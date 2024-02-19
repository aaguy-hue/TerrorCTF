FROM php:8.2-apache
COPY website/ /var/www/html/

# Copy a php.ini file https://github.com/php/php-src/blob/master/php.ini-production
# Perhaps I'll make my own in the future.
RUN mv "$PHP_INI_DIR/php.ini-production" "$PHP_INI_DIR/php.ini"
