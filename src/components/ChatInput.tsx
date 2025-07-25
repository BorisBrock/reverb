import IconButton from "@mui/material/IconButton";
import Divider from "@mui/material/Divider";
import Paper from "@mui/material/Paper";
import InputBase from "@mui/material/InputBase";
import SendIcon from "@mui/icons-material/Send";

export default function ChatInput() {
  return (
    <Paper
      component="form"
      sx={{ p: "2px 4px", display: "flex", alignItems: "center", width: 400 }}
    >
      <InputBase
        sx={{ ml: 1, flex: 1 }}
        placeholder="Enter text message"
        inputProps={{ "aria-label": "Enter text message" }}
      />
      <Divider sx={{ height: 28, m: 0.5 }} orientation="vertical" />
      <IconButton color="primary" sx={{ p: "10px" }} aria-label="directions">
        <SendIcon />
      </IconButton>
    </Paper>
  );
}
