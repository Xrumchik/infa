import React, { useState, useEffect, useRef } from 'react';
import { Button } from './ui/button';
import { Card } from './ui/card';
import { Badge } from './ui/badge';
import { Progress } from './ui/progress';
import { 
  BarChart3, 
  CheckCircle, 
  AlertTriangle, 
  XCircle, 
  Palette, 
  RefreshCw,
  Download,
  Lightbulb
} from 'lucide-react';
import { 
  analyzeColorCompatibility, 
  analyzeStyleHarmony, 
  generateRecommendations,
  CLOTHING_TYPES 
} from '../data/mock';

const StyleAnalysis = ({ userPhoto, selectedClothing, clothingPhotos, onComplete, existingResults }) => {
  const [isAnalyzing, setIsAnalyzing] = useState(false);
  const [progress, setProgress] = useState(0);
  const [results, setResults] = useState(existingResults);
  const [analysisStep, setAnalysisStep] = useState('');
  const canvasRef = useRef(null);

  useEffect(() => {
    if (!existingResults) {
      startAnalysis();
    }
  }, []);

  const extractDominantColors = (imageData) => {
    return new Promise((resolve, reject) => {
      try {
        const canvas = canvasRef.current;
        if (!canvas) {
          reject(new Error('Canvas not available'));
          return;
        }
        
        const ctx = canvas.getContext('2d');
        const img = new Image();
        
        img.onload = () => {
          try {
            canvas.width = 100;
            canvas.height = 100;
            ctx.drawImage(img, 0, 0, 100, 100);
            
            const pixelData = ctx.getImageData(0, 0, 100, 100);
            const data = pixelData.data;
            const colorCounts = {};
            
            // Подсчитываем цвета
            for (let i = 0; i < data.length; i += 16) { // Каждый 4-й пиксель
              const r = Math.floor(data[i] / 40) * 40;
              const g = Math.floor(data[i + 1] / 40) * 40;
              const b = Math.floor(data[i + 2] / 40) * 40;
              const key = `${r},${g},${b}`;
              colorCounts[key] = (colorCounts[key] || 0) + 1;
            }
            
            // Находим доминирующие цвета
            const sortedColors = Object.entries(colorCounts)
              .sort(([,a], [,b]) => b - a)
              .slice(0, 3)
              .map(([color]) => {
                const [r, g, b] = color.split(',').map(Number);
                return { r, g, b, hex: `#${r.toString(16).padStart(2, '0')}${g.toString(16).padStart(2, '0')}${b.toString(16).padStart(2, '0')}` };
              });
            
            resolve(sortedColors);
          } catch (error) {
            console.error('Ошибка при анализе цветов:', error);
            reject(error);
          }
        };
        
        img.onerror = (error) => {
          console.error('Ошибка загрузки изображения:', error);
          reject(new Error('Не удалось загрузить изображение для анализа'));
        };
        
        // Устанавливаем crossOrigin для избежания CORS проблем
        img.crossOrigin = 'anonymous';
        img.src = imageData;
      } catch (error) {
        console.error('Общая ошибка в extractDominantColors:', error);
        reject(error);
      }
    });
  };

  const startAnalysis = async () => {
    setIsAnalyzing(true);
    setProgress(0);
    
    try {
      // Шаг 1: Анализ цветов пользователя
      setAnalysisStep('Анализируем цветотип...');
      setProgress(20);
      await new Promise(resolve => setTimeout(resolve, 1000));
      
      let userColors;
      try {
        userColors = await extractDominantColors(userPhoto);
      } catch (error) {
        console.warn('Не удалось проанализировать цвета пользователя:', error);
        // Используем стандартные цвета кожи
        userColors = [
          { r: 210, g: 180, b: 140, hex: '#d2b48c' }, // Средний тон кожи
          { r: 160, g: 120, b: 80, hex: '#a07850' },  // Более темный тон
          { r: 240, g: 220, b: 190, hex: '#f0dcbe' }  // Светлый тон
        ];
      }
      
      // Шаг 2: Анализ цветов одежды
      setAnalysisStep('Анализируем цвета одежды...');
      setProgress(40);
      await new Promise(resolve => setTimeout(resolve, 1000));
      
      const clothingColors = {};
      for (const clothingId of selectedClothing) {
        if (clothingPhotos[clothingId]) {
          try {
            clothingColors[clothingId] = await extractDominantColors(clothingPhotos[clothingId]);
          } catch (error) {
            console.warn(`Не удалось проанализировать цвета для ${clothingId}:`, error);
            // Используем заглушку цветов
            clothingColors[clothingId] = [
              { r: 128, g: 128, b: 128, hex: '#808080' },
              { r: 64, g: 64, b: 64, hex: '#404040' }
            ];
          }
        }
      }
      
      // Шаг 3: Анализ совместимости цветов
      setAnalysisStep('Оцениваем цветовую гармонию...');
      setProgress(60);
      await new Promise(resolve => setTimeout(resolve, 800));
      
      const colorAnalysis = analyzeColorCompatibility(userColors, clothingColors);
      
      // Шаг 4: Анализ стиля
      setAnalysisStep('Анализируем стилевое сочетание...');
      setProgress(80);
      await new Promise(resolve => setTimeout(resolve, 800));
      
      const styleAnalysis = analyzeStyleHarmony(selectedClothing);
      
      // Шаг 5: Генерация рекомендаций
      setAnalysisStep('Формируем рекомендации...');
      setProgress(90);
      await new Promise(resolve => setTimeout(resolve, 500));
      
      const recommendations = generateRecommendations(colorAnalysis, styleAnalysis, selectedClothing);
      
      setProgress(100);
      await new Promise(resolve => setTimeout(resolve, 300));
      
      const analysisResults = {
        userColors,
        clothingColors,
        colorAnalysis,
        styleAnalysis,
        recommendations,
        overallScore: Math.round((colorAnalysis.score + styleAnalysis.score) / 2),
        timestamp: new Date().toISOString()
      };
      
      setResults(analysisResults);
      onComplete({ results: analysisResults });
      
    } catch (error) {
      console.error('Ошибка анализа:', error);
      
      // Более детальное сообщение об ошибке
      let errorMessage = 'Произошла ошибка при анализе.';
      if (error.message) {
        errorMessage += ` Детали: ${error.message}`;
      }
      
      // Показываем ошибку пользователю
      setAnalysisStep('Ошибка анализа: ' + errorMessage);
      
      // Автоматически скрываем ошибку через 5 секунд
      setTimeout(() => {
        setAnalysisStep('');
        setIsAnalyzing(false);
      }, 5000);
      
      return; // Не устанавливаем isAnalyzing в false сразу
    }
  };

  const getScoreColor = (score) => {
    if (score >= 80) return 'text-green-600';
    if (score >= 60) return 'text-yellow-600';
    return 'text-red-600';
  };

  const getScoreIcon = (score) => {
    if (score >= 80) return <CheckCircle className="text-green-500" size={20} />;
    if (score >= 60) return <AlertTriangle className="text-yellow-500" size={20} />;
    return <XCircle className="text-red-500" size={20} />;
  };

  const saveResults = () => {
    if (!results) return;
    
    const dataStr = JSON.stringify(results, null, 2);
    const dataUri = 'data:application/json;charset=utf-8,'+ encodeURIComponent(dataStr);
    
    const exportFileDefaultName = `stylefit-analysis-${new Date().toISOString().split('T')[0]}.json`;
    
    const linkElement = document.createElement('a');
    linkElement.setAttribute('href', dataUri);
    linkElement.setAttribute('download', exportFileDefaultName);
    linkElement.click();
  };

  if (isAnalyzing) {
    return (
      <div className="text-center space-y-6 py-12">
        <div className="mx-auto w-24 h-24 bg-blue-100 rounded-full flex items-center justify-center">
          <BarChart3 className="text-blue-500 animate-pulse" size={48} />
        </div>
        
        <div>
          <h2 className="text-2xl font-bold text-gray-800 mb-2">Анализируем ваш стиль</h2>
          <p className="text-gray-600 mb-6">{analysisStep}</p>
          
          <div className="max-w-md mx-auto">
            <Progress value={progress} className="mb-2" />
            <p className="text-sm text-gray-500">{progress}% завершено</p>
          </div>
        </div>
      </div>
    );
  }

  if (!results) {
    return (
      <div className="text-center space-y-4">
        <p className="text-gray-600">Произошла ошибка при анализе</p>
        <Button onClick={startAnalysis}>Попробовать снова</Button>
      </div>
    );
  }

  return (
    <div className="space-y-6">
      <div className="text-center">
        <h2 className="text-2xl font-bold text-gray-800 mb-2">Результаты анализа</h2>
        <div className="flex items-center justify-center space-x-2">
          {getScoreIcon(results.overallScore)}
          <span className={`text-2xl font-bold ${getScoreColor(results.overallScore)}`}>
            {results.overallScore}/100
          </span>
        </div>
      </div>

      {/* Общая оценка */}
      <Card className="p-6">
        <div className="flex items-center justify-between mb-4">
          <h3 className="text-lg font-semibold">Общая оценка образа</h3>
          <div className="flex space-x-2">
            <Button variant="outline" size="sm" onClick={startAnalysis}>
              <RefreshCw size={14} className="mr-1" />
              Перезапустить
            </Button>
            <Button variant="outline" size="sm" onClick={saveResults}>
              <Download size={14} className="mr-1" />
              Сохранить
            </Button>
          </div>
        </div>
        
        <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
          <div>
            <div className="flex items-center space-x-2 mb-2">
              <Palette size={16} />
              <span className="font-medium">Цветовая гармония</span>
              <Badge variant={results.colorAnalysis.score >= 70 ? "default" : "destructive"}>
                {results.colorAnalysis.score}%
              </Badge>
            </div>
            <p className="text-sm text-gray-600">{results.colorAnalysis.description}</p>
          </div>
          
          <div>
            <div className="flex items-center space-x-2 mb-2">
              <BarChart3 size={16} />
              <span className="font-medium">Стилевое сочетание</span>
              <Badge variant={results.styleAnalysis.score >= 70 ? "default" : "destructive"}>
                {results.styleAnalysis.score}%
              </Badge>
            </div>
            <p className="text-sm text-gray-600">{results.styleAnalysis.description}</p>
          </div>
        </div>
      </Card>

      {/* Анализ цветов */}
      <Card className="p-6">
        <h3 className="text-lg font-semibold mb-4">Цветовой анализ</h3>
        
        <div className="space-y-4">
          <div>
            <h4 className="font-medium mb-2">Ваш цветотип</h4>
            <div className="flex space-x-2 mb-2">
              {results.userColors.map((color, index) => (
                <div key={index} className="flex items-center space-x-1">
                  <div 
                    className="w-6 h-6 rounded-full border-2 border-gray-300"
                    style={{ backgroundColor: color.hex }}
                    title={`RGB(${color.r}, ${color.g}, ${color.b})`}
                  />
                  <span className="text-xs">{color.hex}</span>
                </div>
              ))}
            </div>
          </div>
          
          <div>
            <h4 className="font-medium mb-2">Цвета одежды</h4>
            <div className="grid grid-cols-1 md:grid-cols-2 gap-3">
              {Object.entries(results.clothingColors).map(([clothingId, colors]) => {
                const clothingType = CLOTHING_TYPES.find(t => t.id === clothingId);
                return (
                  <div key={clothingId} className="flex items-center space-x-2">
                    <span className="text-sm font-medium w-20">{clothingType?.name}</span>
                    <div className="flex space-x-1">
                      {colors.slice(0, 2).map((color, index) => (
                        <div
                          key={index}
                          className="w-4 h-4 rounded-full border border-gray-300"
                          style={{ backgroundColor: color.hex }}
                          title={color.hex}
                        />
                      ))}
                    </div>
                  </div>
                );
              })}
            </div>
          </div>
        </div>
      </Card>

      {/* Рекомендации */}
      {results.recommendations.length > 0 && (
        <Card className="p-6">
          <div className="flex items-center space-x-2 mb-4">
            <Lightbulb className="text-yellow-500" size={20} />
            <h3 className="text-lg font-semibold">Рекомендации по улучшению</h3>
          </div>
          
          <div className="space-y-3">
            {results.recommendations.map((rec, index) => (
              <div key={index} className={`p-3 rounded-md border-l-4 ${
                rec.type === 'positive' ? 'border-green-500 bg-green-50' :
                rec.type === 'warning' ? 'border-yellow-500 bg-yellow-50' :
                'border-red-500 bg-red-50'
              }`}>
                <div className="flex items-start space-x-2">
                  {rec.type === 'positive' ? <CheckCircle className="text-green-500 mt-0.5" size={16} /> :
                   rec.type === 'warning' ? <AlertTriangle className="text-yellow-500 mt-0.5" size={16} /> :
                   <XCircle className="text-red-500 mt-0.5" size={16} />}
                  <div>
                    <p className="font-medium text-sm">{rec.title}</p>
                    <p className="text-sm text-gray-600">{rec.message}</p>
                  </div>
                </div>
              </div>
            ))}
          </div>
        </Card>
      )}

      <canvas ref={canvasRef} style={{ display: 'none' }} />
    </div>
  );
};

export default StyleAnalysis;