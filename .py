import cv2
import face_recognition

def face_recognition_system():
    # Load known images and encode them
    known_face_encodings = []
    known_face_names = []

    # Example: Load 2 people (you can add more)
    img1 = face_recognition.load_image_file("person1.jpg")
    img1_encoding = face_recognition.face_encodings(img1)[0]
    known_face_encodings.append(img1_encoding)
    known_face_names.append("Person 1")

    img2 = face_recognition.load_image_file("person2.jpg")
    img2_encoding = face_recognition.face_encodings(img2)[0]
    known_face_encodings.append(img2_encoding)
    known_face_names.append("Person 2")

    # Open webcam
    cap = cv2.VideoCapture(0)
    print("Press 'q' to quit...")

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Resize frame for speed
        small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_small_frame = cv2.cvtColor(small_frame, cv2.COLOR_BGR2RGB)

        # Detect faces and encode
        face_locations = face_recognition.face_locations(rgb_small_frame)
        face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)

        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"

            if True in matches:
                first_match_index = matches.index(True)
                name = known_face_names[first_match_index]

            # Scale back face location
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4

            # Draw a box around the face
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 255, 0), 3)
            # Label with name
            cv2.putText(frame, name, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

        cv2.imshow("Face Recognition System", frame)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    face_recognition_system()
