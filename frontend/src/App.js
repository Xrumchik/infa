import React, { useState, useEffect } from 'react';
import { BrowserRouter, Routes, Route } from 'react-router-dom';
import './App.css';
import PhotoUpload from './components/PhotoUpload';
import ClothingSelection from './components/ClothingSelection';
import StyleAnalysis from './components/StyleAnalysis';
import { Button } from './components/ui/button';
import { Card } from './components/ui/card';
import { ChevronLeft, Sparkles, Camera, Shirt, BarChart3 } from 'lucide-react';

function App() {
  const [currentStep, setCurrentStep] = useState(1);
  const [userPhoto, setUserPhoto] = useState(null);
  const [selectedClothing, setSelectedClothing] = useState([]);
  const [clothingPhotos, setClothingPhotos] = useState({});
  const [analysisResults, setAnalysisResults] = useState(null);

  const steps = [
    { id: 1, title: 'Загрузите фото', icon: Camera, description: 'Сделайте фото или загрузите из галереи' },
    { id: 2, title: 'Выберите одежду', icon: Shirt, description: 'Отметьте что на вас надето' },
    { id: 3, title: 'Анализ стиля', icon: BarChart3, description: 'Получите персональные рекомендации' }
  ];

  useEffect(() => {
    // Загружаем сохраненные данные
    const savedData = localStorage.getItem('stylefit-data');
    if (savedData) {
      const data = JSON.parse(savedData);
      setUserPhoto(data.userPhoto || null);
      setSelectedClothing(data.selectedClothing || []);
      setClothingPhotos(data.clothingPhotos || {});
      setAnalysisResults(data.analysisResults || null);
    }
  }, []);

  const saveData = () => {
    const data = {
      userPhoto,
      selectedClothing,
      clothingPhotos,
      analysisResults
    };
    localStorage.setItem('stylefit-data', JSON.stringify(data));
  };

  useEffect(() => {
    saveData();
  }, [userPhoto, selectedClothing, clothingPhotos, analysisResults]);

  const handleStepComplete = (stepData) => {
    switch (currentStep) {
      case 1:
        setUserPhoto(stepData.photo);
        setCurrentStep(2);
        break;
      case 2:
        setSelectedClothing(stepData.clothing);
        setClothingPhotos(stepData.photos);
        setCurrentStep(3);
        break;
      case 3:
        setAnalysisResults(stepData.results);
        break;
      default:
        break;
    }
  };

  const resetProcess = () => {
    setCurrentStep(1);
    setUserPhoto(null);
    setSelectedClothing([]);
    setClothingPhotos({});
    setAnalysisResults(null);
    localStorage.removeItem('stylefit-data');
  };

  const goToPreviousStep = () => {
    if (currentStep > 1) {
      setCurrentStep(currentStep - 1);
    }
  };

  const renderStepIndicator = () => (
    <div className="w-full max-w-4xl mx-auto mb-8">
      <div className="flex items-center justify-between">
        {steps.map((step, index) => {
          const Icon = step.icon;
          const isActive = currentStep === step.id;
          const isCompleted = currentStep > step.id;
          
          return (
            <div key={step.id} className="flex flex-col items-center flex-1">
              <div className={`
                w-12 h-12 rounded-full flex items-center justify-center mb-2 transition-all duration-300
                ${isActive ? 'bg-blue-500 text-white scale-110' : 
                  isCompleted ? 'bg-green-500 text-white' : 'bg-gray-200 text-gray-500'}
              `}>
                <Icon size={24} />
              </div>
              <div className="text-center">
                <h3 className={`font-semibold text-sm ${isActive ? 'text-blue-600' : isCompleted ? 'text-green-600' : 'text-gray-500'}`}>
                  {step.title}
                </h3>
                <p className="text-xs text-gray-500 mt-1">{step.description}</p>
              </div>
              {index < steps.length - 1 && (
                <div className={`
                  absolute top-6 left-1/2 w-24 h-0.5 transform translate-x-6
                  ${isCompleted ? 'bg-green-500' : 'bg-gray-200'}
                `} style={{marginLeft: '3rem'}} />
              )}
            </div>
          );
        })}
      </div>
    </div>
  );

  const renderCurrentStep = () => {
    switch (currentStep) {
      case 1:
        return (
          <PhotoUpload 
            onComplete={handleStepComplete}
            existingPhoto={userPhoto}
          />
        );
      case 2:
        return (
          <ClothingSelection 
            onComplete={handleStepComplete}
            userPhoto={userPhoto}
            existingClothing={selectedClothing}
            existingPhotos={clothingPhotos}
          />
        );
      case 3:
        return (
          <StyleAnalysis 
            userPhoto={userPhoto}
            selectedClothing={selectedClothing}
            clothingPhotos={clothingPhotos}
            onComplete={handleStepComplete}
            existingResults={analysisResults}
          />
        );
      default:
        return null;
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-50 to-indigo-100">
      <BrowserRouter>
        <div className="container mx-auto px-4 py-8">
          {/* Header */}
          <header className="text-center mb-8">
            <div className="flex items-center justify-center mb-4">
              <Sparkles className="text-blue-500 mr-3" size={32} />
              <h1 className="text-4xl font-bold text-gray-800">StyleFit</h1>
            </div>
            <p className="text-gray-600 text-lg">Ваш персональный стилист</p>
            <p className="text-sm text-green-600 mt-2 bg-green-50 inline-block px-3 py-1 rounded-full">
              🔒 Ваши фото обрабатываются локально и никуда не передаются
            </p>
          </header>

          {/* Step Indicator */}
          {renderStepIndicator()}

          {/* Navigation */}
          <div className="flex justify-between items-center mb-6 max-w-4xl mx-auto">
            <Button 
              variant="outline" 
              onClick={goToPreviousStep}
              disabled={currentStep === 1}
              className="flex items-center"
            >
              <ChevronLeft size={16} className="mr-1" />
              Назад
            </Button>
            
            <Button 
              variant="outline" 
              onClick={resetProcess}
              className="text-red-600 border-red-200 hover:bg-red-50"
            >
              Начать заново
            </Button>
          </div>

          {/* Main Content */}
          <main className="max-w-4xl mx-auto">
            <Card className="p-6 shadow-lg">
              {renderCurrentStep()}
            </Card>
          </main>

          {/* Footer */}
          <footer className="text-center mt-12 text-gray-500 text-sm">
            <p>StyleFit © 2024 | Анализ стиля и совместимости одежды</p>
          </footer>
        </div>
      </BrowserRouter>
    </div>
  );
}

export default App;