import cv2
import urllib.request
from ultralytics import YOLO


url = 'http://192.168.1.107:81/stream'  #http://192.168.207.167:81/stream
model_path = "E:/LTI/dataset/OpenMind/yolo_organik_anorganik/weights/best.pt"  # ubah ke lokasi model kamu, misal: "runs/detect/train/weights/best.pt"
model = YOLO(model_path)

print("Menguji koneksi ke ESP32-CAM...")
try:
    response = urllib.request.urlopen(url, timeout=5)
    print("✅ Stream dapat diakses (status):", response.status)
except Exception as e:
    print("❌ Tidak dapat terhubung ke ESP32-CAM:", e)
    exit()

print("Membuka stream video...")
cap = cv2.VideoCapture(url)

if not cap.isOpened():
    print("❌ Tidak dapat membuka kamera atau sumber video.")
    exit()


while True:
    ret, frame = cap.read()
    if not ret:
        print("⚠️ Tidak menerima frame, stream mungkin putus.")
        break
    
    results = model(frame, stream=True)

    # 5️⃣ Tampilkan hasil deteksi di jendela OpenCV
    for r in results:
        annotated_frame = r.plot()  # menggambar bounding box dan label
        cv2.imshow("YOLOv8 Live Detection", annotated_frame)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
