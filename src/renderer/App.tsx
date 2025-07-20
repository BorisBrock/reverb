import { MemoryRouter as Router, Routes, Route } from 'react-router-dom';
import { useState } from 'react';
import { Box, Button, TextField, Typography } from '@mui/material';
import icon from '../../assets/icon.svg';
import './App.css';

function Hello() {
  const [name, setName] = useState('');

  return (
    <Box textAlign="center" p={2}>
      <div className="Hello">
        <img width="200" alt="icon" src={icon} />
      </div>
      <h1>electron-react-boilerplate</h1>

      <Box mt={2}>
        <Typography variant="h6" gutterBottom>
          Enter your name
        </Typography>
        <TextField
          label="Name"
          variant="outlined"
          value={name}
          onChange={(e) => setName(e.target.value)}
        />
      </Box>

      <Box mt={2}>
        <Button
          variant="contained"
          onClick={() => {
            if (name) {
              alert(`Hello, ${name}!`);
            }
          }}
        >
          Submit
        </Button>
      </Box>

      <div className="Hello">
        <a
          href="https://electron-react-boilerplate.js.org/"
          target="_blank"
          rel="noreferrer"
        >
          <button type="button">
            <span role="img" aria-label="books">
              📚
            </span>
            Read our docs
          </button>
        </a>
        <a
          href="https://github.com/sponsors/electron-react-boilerplate"
          target="_blank"
          rel="noreferrer"
        >
          <button type="button">
            <span role="img" aria-label="folded hands">
              🙏
            </span>
            Donate
          </button>
        </a>
      </div>
    </Box>
  );
}

export default function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<Hello />} />
      </Routes>
    </Router>
  );
}
