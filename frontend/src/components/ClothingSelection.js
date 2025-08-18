import React, { useState, useRef } from 'react';
import { Button } from './ui/button';
import { Card } from './ui/card';
import { Badge } from './ui/badge';
import { Upload, X, Plus, ArrowRight } from 'lucide-react';
import { CLOTHING_TYPES } from '../data/mock';

const ClothingSelection = ({ onComplete, userPhoto, existingClothing, existingPhotos }) => {
  const [selectedClothing, setSelectedClothing] = useState(existingClothing || []);
  const [clothingPhotos, setClothingPhotos] = useState(existingPhotos || {});
  const fileInputRefs = useRef({});

  const handleClothingToggle = (clothingType) => {
    setSelectedClothing(prev => {
      if (prev.includes(clothingType)) {
        // Удаляем элемент одежды и его фото
        const newPhotos = { ...clothingPhotos };
        delete newPhotos[clothingType];
        setClothingPhotos(newPhotos);
        return prev.filter(item => item !== clothingType);
      } else {
        return [...prev, clothingType];
      }
    });
  };

  const handlePhotoUpload = (clothingType, event) => {
    const file = event.target.files[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = (e) => {
        setClothingPhotos(prev => ({
          ...prev,
          [clothingType]: e.target.result
        }));
      };
      reader.readAsDataURL(file);
    }
  };

  const removePhoto = (clothingType) => {
    setClothingPhotos(prev => {
      const newPhotos = { ...prev };
      delete newPhotos[clothingType];
      return newPhotos;
    });
    
    // Сбрасываем значение input
    if (fileInputRefs.current[clothingType]) {
      fileInputRefs.current[clothingType].value = '';
    }
  };

  const handleComplete = () => {
    if (selectedClothing.length > 0) {
      onComplete({ 
        clothing: selectedClothing, 
        photos: clothingPhotos 
      });
    } else {
      alert('Выберите хотя бы один элемент одежды');
    }
  };

  const canProceed = selectedClothing.length > 0 && 
    selectedClothing.every(item => clothingPhotos[item]);

  return (
    <div className="space-y-6">
      <div className="text-center">
        <h2 className="text-2xl font-bold text-gray-800 mb-2">Выберите вашу одежду</h2>
        <p className="text-gray-600">
          Отметьте что на вас надето и загрузите фото каждого элемента
        </p>
      </div>

      {/* Превью фото пользователя */}
      {userPhoto && (
        <Card className="p-4">
          <div className="flex items-center space-x-4">
            <img 
              src={userPhoto} 
              alt="Ваше фото" 
              className="w-20 h-20 object-cover rounded-lg"
            />
            <div>
              <h3 className="font-semibold">Ваше фото загружено</h3>
              <p className="text-sm text-gray-600">Теперь выберите элементы одежды</p>
            </div>
          </div>
        </Card>
      )}

      {/* Выбор типов одежды */}
      <Card className="p-6">
        <h3 className="text-lg font-semibold mb-4">Типы одежды</h3>
        <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-3">
          {CLOTHING_TYPES.map((type) => (
            <Button
              key={type.id}
              variant={selectedClothing.includes(type.id) ? "default" : "outline"}
              onClick={() => handleClothingToggle(type.id)}
              className="h-auto p-3 flex flex-col items-center space-y-2"
            >
              <span className="text-2xl">{type.icon}</span>
              <span className="text-sm font-medium">{type.name}</span>
            </Button>
          ))}
        </div>
      </Card>

      {/* Загрузка фото выбранных элементов */}
      {selectedClothing.length > 0 && (
        <Card className="p-6">
          <h3 className="text-lg font-semibold mb-4">
            Загрузите фото выбранных элементов
            <Badge variant="secondary" className="ml-2">
              {Object.keys(clothingPhotos).length}/{selectedClothing.length}
            </Badge>
          </h3>
          
          <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
            {selectedClothing.map((clothingId) => {
              const clothingType = CLOTHING_TYPES.find(t => t.id === clothingId);
              const hasPhoto = clothingPhotos[clothingId];
              
              return (
                <Card key={clothingId} className="p-4">
                  <div className="flex items-center justify-between mb-3">
                    <div className="flex items-center space-x-2">
                      <span className="text-xl">{clothingType.icon}</span>
                      <span className="font-medium">{clothingType.name}</span>
                    </div>
                    <Button
                      variant="ghost"
                      size="sm"
                      onClick={() => handleClothingToggle(clothingId)}
                      className="text-red-500 hover:text-red-700"
                    >
                      <X size={16} />
                    </Button>
                  </div>
                  
                  {!hasPhoto ? (
                    <div>
                      <input
                        ref={el => fileInputRefs.current[clothingId] = el}
                        type="file"
                        accept="image/*"
                        onChange={(e) => handlePhotoUpload(clothingId, e)}
                        className="hidden"
                      />
                      <Button
                        variant="outline"
                        onClick={() => fileInputRefs.current[clothingId]?.click()}
                        className="w-full border-dashed border-2 h-24 hover:bg-gray-50"
                      >
                        <div className="text-center">
                          <Upload className="mx-auto mb-1" size={20} />
                          <span className="text-sm">Загрузить фото</span>
                        </div>
                      </Button>
                    </div>
                  ) : (
                    <div className="relative">
                      <img
                        src={clothingPhotos[clothingId]}
                        alt={clothingType.name}
                        className="w-full h-24 object-cover rounded-md"
                      />
                      <Button
                        variant="destructive"
                        size="sm"
                        onClick={() => removePhoto(clothingId)}
                        className="absolute top-1 right-1 w-6 h-6 p-0"
                      >
                        <X size={12} />
                      </Button>
                    </div>
                  )}
                </Card>
              );
            })}
          </div>
        </Card>
      )}

      {/* Кнопка продолжения */}
      <div className="flex justify-center">
        <Button
          onClick={handleComplete}
          disabled={!canProceed}
          size="lg"
          className="bg-green-500 hover:bg-green-600 disabled:bg-gray-300"
        >
          {!canProceed ? (
            <>
              <Plus className="mr-2" size={16} />
              Добавьте фото всех элементов
            </>
          ) : (
            <>
              <ArrowRight className="mr-2" size={16} />
              Анализировать стиль
            </>
          )}
        </Button>
      </div>
    </div>
  );
};

export default ClothingSelection;