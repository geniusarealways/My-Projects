
// DOM Elements
const video = document.getElementById('video');
const canvas = document.getElementById('output-canvas');
const ctx = canvas.getContext('2d');
const startBtn = document.getElementById('start-btn');
const feedback = document.getElementById('feedback');
const repCount = document.getElementById('rep-count');
const totalRepsEl = document.getElementById('total-reps');
const accuracyEl = document.getElementById('accuracy');
const durationEl = document.getElementById('duration');
const sensitivitySlider = document.getElementById('sensitivity');
const sensitivityValue = document.getElementById('sensitivity-value');
const toggleDarkMode = document.getElementById('toggle-dark-mode');

// Dashboard Elements
const dailyTotalEl = document.getElementById('daily-total');
const weeklyTotalEl = document.getElementById('weekly-total');
const bestStreakEl = document.getElementById('best-streak');
const achievementsEl = document.getElementById('achievements');

// State
let repCountVal = 0;
let repInProgress = false;
let lastShoulderY = null;
let minShoulderDiff = 25; // Default sensitivity
let startTime;
let validReps = 0;
let totalRepsAnalyzed = 0;
let cameraActive = false;

// Progress Data (stored in localStorage)
const progressKey = 'pushupProgress';
let progressData = JSON.parse(localStorage.getItem(progressKey)) || {
  dates: {},
  achievements: 0,
  streak: 0,
  bestStreak: 0
};

// Initialize Chart
const weeklyChartCtx = document.getElementById('weekly-chart').getContext('2d');
let weeklyChart;

// Update sensitivity display
sensitivitySlider.addEventListener('input', () => {
  minShoulderDiff = parseInt(sensitivitySlider.value);
  sensitivityValue.textContent = minShoulderDiff;
});

// Toggle Dark Mode
toggleDarkMode.addEventListener('click', () => {
  document.body.classList.toggle('dark-mode');
  toggleDarkMode.textContent = document.body.classList.contains('dark-mode') ? '☀️ Light Mode' : '🌙 Dark Mode';
});

// Scroll to section
function scrollToSection(id) {
  document.getElementById(id).scrollIntoView({ behavior: 'smooth' });
}

// Start Camera and Pose Detection
startBtn.addEventListener('click', async () => {
  if (cameraActive) {
    stopCamera();
    return;
  }

  try {
    const stream = await navigator.mediaDevices.getUserMedia({ video: true });
    video.srcObject = stream;

    // Wait for video to load
    video.onloadedmetadata = () => {
      canvas.width = video.videoWidth;
      canvas.height = video.videoHeight;
      startBtn.textContent = "Stop Camera";
      cameraActive = true;
      startSession();
      runPoseDetection();
    };
  } catch (err) {
    feedback.textContent = "Camera access denied. Please allow camera.";
    console.error("Camera error:", err);
  }
});

function startSession() {
  startTime = Date.now();
  repCountVal = 0;
  validReps = 0;
  totalRepsAnalyzed = 0;
  lastShoulderY = null;
  repInProgress = false;
  updateSessionSummary();
  startTimer();
}

function stopCamera() {
  const stream = video.srcObject;
  const tracks = stream.getTracks();
  tracks.forEach(track => track.stop());
  video.srcObject = null;
  startBtn.textContent = "Start Camera";
  cameraActive = false;
  feedback.textContent = "Camera stopped.";
}

function startTimer() {
  setInterval(() => {
    const elapsed = Math.floor((Date.now() - startTime) / 1000);
    const mins = Math.floor(elapsed / 60).toString().padStart(2, '0');
    const secs = (elapsed % 60).toString().padStart(2, '0');
    durationEl.textContent = `${mins}:${secs}`;
  }, 1000);
}

// Update session summary
function updateSessionSummary() {
  totalRepsEl.textContent = repCountVal;
  const acc = validReps > 0 ? Math.round((validReps / totalRepsAnalyzed) * 100) : 0;
  accuracyEl.textContent = acc;
}

// Save progress to localStorage
function saveProgress() {
  const today = new Date().toISOString().split('T')[0];
  if (!progressData.dates[today]) {
    progressData.dates[today] = 0;
  }
  progressData.dates[today] += repCountVal;

  // Update streak
  const dates = Object.keys(progressData.dates).sort();
  let currentStreak = 0;
  for (let i = dates.length - 1; i >= 0; i--) {
    const date = dates[i];
    const day = new Date(date);
    const todayDate = new Date();
    const diffTime = Math.abs(todayDate - day);
    const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    if (diffDays <= i && progressData.dates[date] > 0) {
      currentStreak++;
    } else {
      break;
    }
  }
  progressData.streak = currentStreak;
  progressData.bestStreak = Math.max(progressData.bestStreak, currentStreak);

  // Achievements
  if (repCountVal >= 50) progressData.achievements = Math.max(progressData.achievements, 1);
  if (repCountVal >= 100) progressData.achievements = Math.max(progressData.achievements, 2);
  if (progressData.streak >= 7) progressData.achievements = Math.max(progressData.achievements, 3);

  localStorage.setItem(progressKey, JSON.stringify(progressData));
  updateDashboard();
}

// Update Dashboard
function updateDashboard() {
  const today = new Date().toISOString().split('T')[0];
  dailyTotalEl.textContent = progressData.dates[today] || 0;
  
  const weekStart = new Date();
  weekStart.setDate(weekStart.getDate() - 6);
  let weeklyTotal = 0;
  for (let i = 0; i < 7; i++) {
    const date = new Date(weekStart);
    date.setDate(weekStart.getDate() + i);
    const key = date.toISOString().split('T')[0];
    weeklyTotal += progressData.dates[key] || 0;
  }
  weeklyTotalEl.textContent = weeklyTotal;
  bestStreakEl.textContent = progressData.bestStreak;
  achievementsEl.textContent = progressData.achievements;

  updateChart();
}

function updateChart() {
  const labels = [];
  const data = [];
  const weekStart = new Date();
  weekStart.setDate(weekStart.getDate() - 6);
  for (let i = 0; i < 7; i++) {
    const date = new Date(weekStart);
    date.setDate(weekStart.getDate() + i);
    const key = date.toISOString().split('T')[0];
    labels.push(date.toLocaleDateString('en-US', { weekday: 'short' }));
    data.push(progressData.dates[key] || 0);
  }

  if (weeklyChart) weeklyChart.destroy();
  weeklyChart = new Chart(weeklyChartCtx, {
    type: 'bar',
    data: {
      labels,
      datasets: [{
        label: 'Push-Ups',
        data,
        backgroundColor: '#4a90e2',
        borderColor: '#357abd',
        borderWidth: 1
      }]
    },
    options: {
      responsive: true,
      scales: {
        y: {
          beginAtZero: true,
          ticks: {
            color: document.body.classList.contains('dark-mode') ? '#eee' : '#333'
          }
        },
        x: {
          ticks: {
            color: document.body.classList.contains('dark-mode') ? '#eee' : '#333'
          }
        }
      },
      plugins: {
        legend: {
          labels: {
            color: document.body.classList.contains('dark-mode') ? '#eee' : '#333'
          }
        }
      }
    }
  });
}

// Reset progress
document.getElementById('reset-progress').addEventListener('click', () => {
  if (confirm("Reset all progress? This cannot be undone.")) {
    progressData = {
      dates: {},
      achievements: 0,
      streak: 0,
      bestStreak: 0
    };
    localStorage.setItem(progressKey, JSON.stringify(progressData));
    updateDashboard();
  }
});

// Pose Detection with MediaPipe
function runPoseDetection() {
  const pose = new Pose({
    locateFile: (file) => {
      return `https://cdn.jsdelivr.net/npm/@mediapipe/pose/${file}`;
    }
  });

  pose.setOptions({
    modelComplexity: 1,
    smoothLandmarks: true,
    enableSegmentation: false,
    minDetectionConfidence: 0.5,
    minTrackingConfidence: 0.5
  });

  pose.onResults(onResults);

  const camera = new Camera(video, {
    onFrame: async () => {
      if (cameraActive) await pose.send({ image: video });
    },
    width: 640,
    height: 480
  });

  camera.start();
}

function onResults(results) {
  if (!results.poseLandmarks || !cameraActive) return;

  // Clear canvas
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Draw pose lines
  drawConnectors(ctx, results.poseLandmarks, POSE_CONNECTIONS, { color: '#00FF00', lineWidth: 4 });
  drawLandmarks(ctx, results.poseLandmarks, { color: '#FF0000', radius: 5 });

  // Get shoulder landmarks (landmark 11 = left shoulder, 12 = right shoulder)
  const leftShoulder = results.poseLandmarks[11];
  const rightShoulder = results.poseLandmarks[12];

  // Average Y position of shoulders
  const shoulderY = (leftShoulder.y + rightShoulder.y) / 2 * canvas.height;

  // Draw shoulder point
  ctx.fillStyle = 'yellow';
  ctx.beginPath();
  ctx.arc((leftShoulder.x + rightShoulder.x) / 2 * canvas.width, shoulderY, 8, 0, 2 * Math.PI);
  ctx.fill();

  if (lastShoulderY === null) {
    lastShoulderY = shoulderY;
    return;
  }

  totalRepsAnalyzed++;

  // Detect downward motion
  if (shoulderY > lastShoulderY + minShoulderDiff && !repInProgress) {
    repInProgress = true;
    feedback.textContent = "Good! Now push up.";
    feedback.className = "good";
  }
  // Detect upward motion to complete rep
  else if (shoulderY < lastShoulderY - minShoulderDiff && repInProgress) {
    repCountVal++;
    validReps++;
    repInProgress = false;
    feedback.textContent = "Good rep! 🎉";
    feedback.className = "good";
    repCount.textContent = repCountVal;
    setTimeout(() => { feedback.className = ""; }, 1000);
  }
  // Not enough motion
  else if (Math.abs(shoulderY - lastShoulderY) < 2) {
    feedback.textContent = "Keep moving... Lower shoulders more.";
    feedback.className = "low";
  }

  lastShoulderY = shoulderY;
  updateSessionSummary();
}

// On page load
window.addEventListener('load', () => {
  updateDashboard();
  // Restore dark mode if previously set
  if (localStorage.getItem('darkMode') === 'enabled') {
    document.body.classList.add('dark-mode');
    toggleDarkMode.textContent = '☀️ Light Mode';
  }
});

// On unload, save progress
window.addEventListener('beforeunload', () => {
  if (cameraActive) {
    saveProgress();
  }
});