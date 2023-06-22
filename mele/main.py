import socket
import threading
import pickle
import Orange.ensembles.ada_boost
from property import machineLearning
with open('malware_adaboost_model.pkcls', 'rb') as file:
    model = pickle.load(file)

HOST = '127.0.0.1'  # Lokal makinenin IP adresi
PORT = 8103        # Bağlanılacak port

def receive_message(sock):
    print("READY!")
    while True:
        try:
            data = sock.recv(2048)
            
            if not data:
                break
            sendedMessage = data.decode('latin-1')
            sendedMessage=sendedMessage[4:]
            fileProperty = machineLearning(sendedMessage)
            prediction =model([fileProperty])
            print(sendedMessage,int(prediction))
            sock.sendall(str(int(prediction)).encode())
        except ConnectionResetError:
            print("Server has disconnected")
            a=None
            input(a)
            exit()
def myMain():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
        except ConnectionRefusedError:
            print("Could not connect to server. Please make sure it is running.")
            a=None
            input(a)
            exit()
        receive_thread = threading.Thread(target=receive_message, args=(s,))
        receive_thread.start()
        receive_thread.join()
if __name__ == "__main__" : 
    myMain()