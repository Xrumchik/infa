// Типы одежды
export const CLOTHING_TYPES = [
  { id: 'shirt', name: 'Рубашка', icon: '👔', category: 'top' },
  { id: 'tshirt', name: 'Футболка', icon: '👕', category: 'top' },
  { id: 'sweater', name: 'Кофта', icon: '🧥', category: 'top' },
  { id: 'jacket', name: 'Куртка', icon: '🧥', category: 'outer' },
  { id: 'jeans', name: 'Джинсы', icon: '👖', category: 'bottom' },
  { id: 'pants', name: 'Брюки', icon: '👔', category: 'bottom' },
  { id: 'shorts', name: 'Шорты', icon: '🩳', category: 'bottom' },
  { id: 'skirt', name: 'Юбка', icon: '👗', category: 'bottom' },
  { id: 'dress', name: 'Платье', icon: '👗', category: 'dress' },
  { id: 'sneakers', name: 'Кроссовки', icon: '👟', category: 'shoes' },
  { id: 'boots', name: 'Ботинки', icon: '👢', category: 'shoes' },
  { id: 'sandals', name: 'Сандалии', icon: '👡', category: 'shoes' },
  { id: 'heels', name: 'Каблуки', icon: '👠', category: 'shoes' },
  { id: 'hat', name: 'Шапка', icon: '🎩', category: 'accessory' },
  { id: 'bag', name: 'Сумка', icon: '👜', category: 'accessory' },
  { id: 'watch', name: 'Часы', icon: '⌚', category: 'accessory' }
];

// Правила стилевой совместимости
export const STYLE_RULES = [
  {
    items: ['sneakers', 'dress'],
    score: 40,
    message: 'Кроссовки с платьем могут выглядеть неформально. Рассмотрите туфли для более элегантного образа.'
  },
  {
    items: ['shorts', 'jacket'],
    score: 60,
    message: 'Шорты с пиджаком создают смешение стилей. Подойдет для casual-smart образа.'
  },
  {
    items: ['jeans', 'shirt'],
    score: 85,
    message: 'Классическое сочетание джинсов и рубашки - универсальный выбор.'
  },
  {
    items: ['tshirt', 'jeans'],
    score: 90,
    message: 'Идеальное повседневное сочетание футболки и джинсов.'
  },
  {
    items: ['dress', 'heels'],
    score: 95,
    message: 'Платье с каблуками - элегантное и женственное сочетание.'
  },
  {
    items: ['pants', 'shirt'],
    score: 88,
    message: 'Классические брюки с рубашкой подходят для деловых встреч.'
  }
];

// Цветовые правила (упрощенные)
export const COLOR_HARMONY_RULES = [
  {
    name: 'Монохроматическая гармония',
    check: (colors) => {
      // Проверяем, находятся ли цвета в одной цветовой группе
      const hues = colors.map(c => rgbToHsl(c.r, c.g, c.b)[0]);
      const range = Math.max(...hues) - Math.min(...hues);
      return range < 30;
    },
    score: 85,
    message: 'Цвета хорошо сочетаются в одной цветовой гамме'
  },
  {
    name: 'Комплементарная гармония',
    check: (colors) => {
      if (colors.length < 2) return false;
      const hues = colors.map(c => rgbToHsl(c.r, c.g, c.b)[0]);
      // Проверяем, есть ли комплементарные цвета (разница ~180°)
      for (let i = 0; i < hues.length; i++) {
        for (let j = i + 1; j < hues.length; j++) {
          const diff = Math.abs(hues[i] - hues[j]);
          if (Math.abs(diff - 180) < 30 || Math.abs(diff - 180) > 330) {
            return true;
          }
        }
      }
      return false;
    },
    score: 80,
    message: 'Комплементарные цвета создают яркий контраст'
  },
  {
    name: 'Аналогическая гармония',
    check: (colors) => {
      if (colors.length < 2) return false;
      const hues = colors.map(c => rgbToHsl(c.r, c.g, c.b)[0]);
      hues.sort((a, b) => a - b);
      
      for (let i = 1; i < hues.length; i++) {
        if (hues[i] - hues[i-1] > 60) return false;
      }
      return true;
    },
    score: 90,
    message: 'Аналогичные цвета создают гармоничное сочетание'
  }
];

// Функция конвертации RGB в HSL
export function rgbToHsl(r, g, b) {
  r /= 255;
  g /= 255;
  b /= 255;

  const max = Math.max(r, g, b);
  const min = Math.min(r, g, b);
  let h, s, l = (max + min) / 2;

  if (max === min) {
    h = s = 0;
  } else {
    const d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    
    switch (max) {
      case r: h = (g - b) / d + (g < b ? 6 : 0); break;
      case g: h = (b - r) / d + 2; break;
      case b: h = (r - g) / d + 4; break;
    }
    h /= 6;
  }

  return [h * 360, s * 100, l * 100];
}

// Анализ совместимости цветов
export function analyzeColorCompatibility(userColors, clothingColors) {
  const allClothingColors = Object.values(clothingColors).flat();
  const allColors = [...userColors, ...allClothingColors];
  
  let bestRule = null;
  let maxScore = 0;
  
  for (const rule of COLOR_HARMONY_RULES) {
    if (rule.check(allColors)) {
      if (rule.score > maxScore) {
        maxScore = rule.score;
        bestRule = rule;
      }
    }
  }
  
  if (bestRule) {
    return {
      score: bestRule.score,
      description: bestRule.message,
      rule: bestRule.name
    };
  }
  
  // Если никакие правила не подошли, даем базовую оценку
  const avgLightness = allColors.reduce((sum, color) => {
    const [,, l] = rgbToHsl(color.r, color.g, color.b);
    return sum + l;
  }, 0) / allColors.length;
  
  const score = avgLightness > 20 && avgLightness < 80 ? 65 : 45;
  
  return {
    score,
    description: score > 60 ? 'Цвета нейтральны и сочетаются' : 'Цвета могут конфликтовать друг с другом',
    rule: 'Базовая оценка'
  };
}

// Анализ стилевой гармонии
export function analyzeStyleHarmony(selectedClothing) {
  let totalScore = 0;
  let ruleCount = 0;
  const appliedRules = [];
  
  // Проверяем все правила для выбранной одежды
  for (const rule of STYLE_RULES) {
    const hasAllItems = rule.items.every(item => selectedClothing.includes(item));
    if (hasAllItems) {
      totalScore += rule.score;
      ruleCount++;
      appliedRules.push(rule);
    }
  }
  
  // Если нет специфических правил, даем среднюю оценку
  if (ruleCount === 0) {
    // Проверяем базовую совместимость категорий
    const categories = selectedClothing.map(id => {
      const item = CLOTHING_TYPES.find(t => t.id === id);
      return item ? item.category : 'unknown';
    });
    
    const hasTop = categories.includes('top');
    const hasBottom = categories.includes('bottom') || categories.includes('dress');
    const hasShoes = categories.includes('shoes');
    
    let baseScore = 70;
    if (hasTop && hasBottom && hasShoes) baseScore = 85;
    else if (hasTop && hasBottom) baseScore = 80;
    else if (categories.includes('dress') && hasShoes) baseScore = 82;
    
    return {
      score: baseScore,
      description: 'Базовое сочетание элементов гардероба',
      appliedRules: []
    };
  }
  
  const avgScore = totalScore / ruleCount;
  const bestRule = appliedRules.reduce((best, current) => 
    current.score > best.score ? current : best
  );
  
  return {
    score: Math.round(avgScore),
    description: bestRule.message,
    appliedRules
  };
}

// Генерация рекомендаций
export function generateRecommendations(colorAnalysis, styleAnalysis, selectedClothing) {
  const recommendations = [];
  
  // Рекомендации по цветам
  if (colorAnalysis.score < 70) {
    recommendations.push({
      type: 'warning',
      title: 'Цветовая гармония',
      message: 'Попробуйте более нейтральные или гармонирующие оттенки. Рассмотрите монохроматические сочетания.'
    });
  } else if (colorAnalysis.score >= 85) {
    recommendations.push({
      type: 'positive',
      title: 'Отличная цветовая гармония',
      message: 'Цвета прекрасно сочетаются друг с другом!'
    });
  }
  
  // Рекомендации по стилю
  if (styleAnalysis.score < 70) {
    recommendations.push({
      type: 'negative',
      title: 'Стилевое несоответствие',
      message: 'Некоторые элементы не сочетаются по стилю. Попробуйте более последовательный образ.'
    });
  } else if (styleAnalysis.score >= 85) {
    recommendations.push({
      type: 'positive',
      title: 'Гармоничный стиль',
      message: 'Элементы одежды прекрасно дополняют друг друга!'
    });
  }
  
  // Специфические рекомендации
  if (selectedClothing.includes('sneakers') && selectedClothing.includes('dress')) {
    recommendations.push({
      type: 'warning',
      title: 'Кроссовки с платьем',
      message: 'Такое сочетание может быть стильным в casual образе, но для более формальных случаев рассмотрите туфли.'
    });
  }
  
  if (selectedClothing.includes('shorts') && selectedClothing.includes('jacket')) {
    recommendations.push({
      type: 'warning',
      title: 'Смешение стилей',
      message: 'Шорты с пиджаком - смелое решение. Убедитесь, что остальные элементы поддерживают этот стиль.'
    });
  }
  
  return recommendations;
}