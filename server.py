import sys
import http.server
import socketserver

PORT = 8080

class HTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
        self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
        http.server.SimpleHTTPRequestHandler.end_headers(self)

def server(port):
    httpd = socketserver.TCPServer(('', port), HTTPRequestHandler)
    return httpd

if __name__ == "__main__":
    port = PORT
    httpd = server(port)
    try:
        print("\nServing at localhost:" + str(port))
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n...Shutting down http server.")
        httpd.shutdown()
        sys.exit()
