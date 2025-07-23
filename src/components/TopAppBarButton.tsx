import * as React from 'react';
import { styled } from '@mui/material/styles';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import Button from '@mui/material/Button';
import IconButton from '@mui/material/IconButton';
import MenuIcon from '@mui/icons-material/Menu';
import FormatAlignLeftIcon from '@mui/icons-material/FormatAlignLeft';
import FormatAlignCenterIcon from '@mui/icons-material/FormatAlignCenter';
import FormatAlignRightIcon from '@mui/icons-material/FormatAlignRight';
import FormatBoldIcon from '@mui/icons-material/FormatBold';
import Divider, { dividerClasses } from '@mui/material/Divider';
import Paper from '@mui/material/Paper';
import Grid from '@mui/material/Grid';
import List from '@mui/material/List';
import ListItem from '@mui/material/ListItem';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemIcon from '@mui/material/ListItemIcon';
import ListItemText from '@mui/material/ListItemText';
import InboxIcon from '@mui/icons-material/Inbox';
import DraftsIcon from '@mui/icons-material/Drafts';
import ListItemAvatar from '@mui/material/ListItemAvatar';
import Avatar from '@mui/material/Avatar';
import InputBase from '@mui/material/InputBase';
import SearchIcon from '@mui/icons-material/Search';
import SendIcon from '@mui/icons-material/Send';
import EditIcon from '@mui/icons-material/Edit';
import DeleteIcon from '@mui/icons-material/Delete';
import DropDownIcon from '@mui/icons-material/ArrowDropDown';
import ServerIcon from '@mui/icons-material/Computer';

interface TopBarButtonProps {
  headline: string;
  content: string;
}

const TopBarButton: React.FC<TopBarButtonProps> = ({ headline, content }) => {
  return (
    <IconButton aria-label="delete">
      <Paper
        elevation={3}
        sx={{
          p: 1,
          display: 'flex',
          alignItems: 'left',
          justifyContent: 'space-between',
          height: 36,
          borderRadius: 2,
        }}
      >

        {/* Left side: Headline and Content */}
        <Box sx={{ display: 'flex', flexDirection: 'column', flexGrow: 1 }}>
          <Typography fontSize="0.6rem" color="text.secondary">
            {headline}
          </Typography>
          <Typography fontSize="0.8rem">{content}</Typography>
        </Box>

        {/* Right side: Icons */}
        <Box sx={{ display: 'flex', gap: 1, ml: 2 }}>
          <IconButton aria-label="delete">
            <DropDownIcon />
          </IconButton>
        </Box>
      </Paper>
    </IconButton>
  );
};

export default TopBarButton;
