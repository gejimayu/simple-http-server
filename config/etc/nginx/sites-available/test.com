server {
	listen 80;
	listen [::]:80;

	root /var/www/test.com/html;
	
	# access_log /var/log/nginx/test.com.log apm gzip;
	access_log off;

	server_name test.com www.test.com;
	
	location /20kb {
		expires 1d;
		try_files /index20KB.html =404;		
	}

	location /500b {
		expires 1d;
		try_files /index500b.html =404;
	}

	location /nginx_status {
		stub_status on;
		allow 127.0.0.1;
		deny all;
	}
}
