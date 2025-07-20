import { MemoryRouter as Router, Routes, Route } from 'react-router-dom';
import * as React from 'react';
import { styled } from '@mui/material/styles';
import Grid from '@mui/material/Grid';

import TopAppBar from '../components/TopAppBar';
import PersonList from '../components/PersonList';
import ChatList from '../components/ChatList';
import ChatInput from '../components/ChatInput';

export default function VerticalDividers() {
  return (
    <Grid container spacing={2}>
      <Grid size={6}>
        <PersonList />
      </Grid>
      <Grid size={6}>
        <ChatList />
        <ChatInput />
      </Grid>
    </Grid>
  );
}

export default function App() {
  return (
    <div>
      <TopAppBar />
      <VerticalDividers />
    </div>
  );
}
