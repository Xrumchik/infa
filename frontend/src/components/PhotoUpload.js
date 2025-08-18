import React, { useState, useRef, useEffect } from 'react';
import { Button } from './ui/button';
import { Card } from './ui/card';
import { Camera, Upload, RotateCcw, Check } from 'lucide-react';

const PhotoUpload = ({ onComplete, existingPhoto }) => {
  const [photo, setPhoto] = useState(existingPhoto);
  const [isCapturing, setIsCapturing] = useState(false);
  const [stream, setStream] = useState(null);
  const videoRef = useRef(null);
  const canvasRef = useRef(null);
  const fileInputRef = useRef(null);

  useEffect(() => {
    return () => {
      if (stream) {
        stream.getTracks().forEach(track => track.stop());
      }
    };
  }, [stream]);

  const startCamera = async () => {
    try {
      const mediaStream = await navigator.mediaDevices.getUserMedia({
        video: { facingMode: 'user', width: 640, height: 480 }
      });
      setStream(mediaStream);
      setIsCapturing(true);
      
      if (videoRef.current) {
        videoRef.current.srcObject = mediaStream;
      }
    } catch (error) {
      console.error('Ошибка доступа к камере:', error);
      alert('Не удалось получить доступ к камере. Попробуйте загрузить фото из файла.');
    }
  };

  const stopCamera = () => {
    if (stream) {
      stream.getTracks().forEach(track => track.stop());
      setStream(null);
    }
    setIsCapturing(false);
  };

  const capturePhoto = () => {
    if (videoRef.current && canvasRef.current) {
      const canvas = canvasRef.current;
      const video = videoRef.current;
      const context = canvas.getContext('2d');
      
      canvas.width = video.videoWidth;
      canvas.height = video.videoHeight;
      
      // Отражаем изображение по горизонтали для селфи
      context.translate(canvas.width, 0);
      context.scale(-1, 1);
      context.drawImage(video, 0, 0);
      
      const imageData = canvas.toDataURL('image/jpeg', 0.8);
      setPhoto(imageData);
      stopCamera();
    }
  };

  const handleFileUpload = (event) => {
    const file = event.target.files[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = (e) => {
        setPhoto(e.target.result);
      };
      reader.readAsDataURL(file);
    }
  };

  const retakePhoto = () => {
    setPhoto(null);
    if (fileInputRef.current) {
      fileInputRef.current.value = '';
    }
  };

  const handleComplete = () => {
    if (photo) {
      onComplete({ photo });
    }
  };

  return (
    <div className="space-y-6">
      <div className="text-center">
        <h2 className="text-2xl font-bold text-gray-800 mb-2">Загрузите ваше фото</h2>
        <p className="text-gray-600">
          Для лучшего анализа используйте фото в полный рост или по пояс на нейтральном фоне
        </p>
      </div>

      {!photo ? (
        <div className="space-y-4">
          {/* Camera Section */}
          {!isCapturing ? (
            <Card className="p-6 text-center border-dashed border-2 border-gray-300 hover:border-blue-400 transition-colors">
              <Camera className="mx-auto mb-4 text-gray-400" size={48} />
              <h3 className="text-lg font-semibold mb-2">Сделать фото</h3>
              <p className="text-gray-600 mb-4">Используйте веб-камеру для быстрого снимка</p>
              <Button onClick={startCamera} className="bg-blue-500 hover:bg-blue-600">
                <Camera className="mr-2" size={16} />
                Включить камеру
              </Button>
            </Card>
          ) : (
            <Card className="p-4">
              <div className="relative">
                <video
                  ref={videoRef}
                  autoPlay
                  playsInline
                  muted
                  className="w-full max-w-md mx-auto rounded-lg bg-black"
                  style={{ transform: 'scaleX(-1)' }}
                />
                <div className="text-center mt-4 space-x-2">
                  <Button onClick={capturePhoto} className="bg-green-500 hover:bg-green-600">
                    <Camera className="mr-2" size={16} />
                    Сделать снимок
                  </Button>
                  <Button onClick={stopCamera} variant="outline">
                    Отмена
                  </Button>
                </div>
              </div>
            </Card>
          )}

          {/* File Upload Section */}
          <div className="text-center">или</div>
          
          <Card className="p-6 text-center border-dashed border-2 border-gray-300 hover:border-blue-400 transition-colors">
            <Upload className="mx-auto mb-4 text-gray-400" size={48} />
            <h3 className="text-lg font-semibold mb-2">Загрузить из файла</h3>
            <p className="text-gray-600 mb-4">Выберите фото из галереи вашего устройства</p>
            <input
              ref={fileInputRef}
              type="file"
              accept="image/*"
              onChange={handleFileUpload}
              className="hidden"
            />
            <Button 
              onClick={() => fileInputRef.current?.click()}
              variant="outline"
            >
              <Upload className="mr-2" size={16} />
              Выбрать файл
            </Button>
          </Card>
        </div>
      ) : (
        <div className="space-y-4">
          <Card className="p-4">
            <div className="text-center">
              <img 
                src={photo} 
                alt="Ваше фото" 
                className="max-w-full max-h-96 mx-auto rounded-lg shadow-md"
              />
              <div className="mt-4 space-x-2">
                <Button onClick={retakePhoto} variant="outline">
                  <RotateCcw className="mr-2" size={16} />
                  Переснять
                </Button>
                <Button onClick={handleComplete} className="bg-green-500 hover:bg-green-600">
                  <Check className="mr-2" size={16} />
                  Продолжить
                </Button>
              </div>
            </div>
          </Card>
        </div>
      )}

      <canvas ref={canvasRef} style={{ display: 'none' }} />
    </div>
  );
};

export default PhotoUpload;