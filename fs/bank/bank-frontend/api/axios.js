import axios from 'axios';
import { getJwt, clearJwt } from '../utils/authStorage.js';

const api = axios.create({
  baseURL: 'http://localhost:3000/api/v1',
});

api.interceptors.request.use((config) => {
  const token = getJwt();
  if (token) {
    config.headers.Authorization = `Bearer ${token}`;
  }
  return config;
});

api.interceptors.response.use(
  (res) => res,
  (err) => {
    if (err.response?.status === 401) {
      clearJwt();
      window.location.href = '/login';
    }
    return Promise.reject(err);
  }
);

export default api;
