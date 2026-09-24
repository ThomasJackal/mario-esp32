import socket
import threading

import keyboard

HOST = '0.0.0.0'
PORT = 10000

KEY_MAP = {
    'z': 'UP',
    'q': 'LEFT',
    's': 'DOWN',
    'd': 'RIGHT',
    'shift': 'A',
    'space': 'B',
}

client_lock = threading.Lock()
current_client = None
pressed = set()


def send_event(button, state):
    """Send '<BUTTON>:<state>\n' to the connected ESP32 (state: 1=down, 0=up)."""
    global current_client
    message = "{}:{}\n".format(button, state).encode()
    with client_lock:
        client = current_client
    if client is not None:
        try:
            client.sendall(message)
        except OSError:
            pass
    print("{}:{}".format(button, state))


def on_key(event):
    name = event.name.lower() if event.name else ''
    button = KEY_MAP.get(name)
    if button is None:
        return

    if event.event_type == keyboard.KEY_DOWN:
        if button in pressed:
            return  # ignore auto-repeat while the key is held
        pressed.add(button)
        send_event(button, 1)
    elif event.event_type == keyboard.KEY_UP:
        pressed.discard(button)
        send_event(button, 0)


def main():
    global current_client

    keyboard.hook(on_key)

    s = socket.socket()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    s.settimeout(1.0)

    print("Server listening on {}:{} ...".format(HOST, PORT))
    print("Keys: Z/Q/S/D = UP/LEFT/DOWN/RIGHT, LeftShift = A, Space = B")
    print("Press Ctrl+C to stop.")

    try:
        while True:
            try:
                client, addr = s.accept()
            except socket.timeout:
                continue

            print("ESP32 connected from {}".format(addr))
            with client_lock:
                current_client = client

            # Keep the connection open; only used to detect disconnection.
            try:
                while True:
                    data = client.recv(32)
                    if len(data) == 0:
                        break
            except OSError:
                pass
            finally:
                with client_lock:
                    current_client = None
                client.close()
                print("Client disconnected")
    except KeyboardInterrupt:
        print("\nServer stopped")
    finally:
        keyboard.unhook_all()
        s.close()


if __name__ == "__main__":
    main()
