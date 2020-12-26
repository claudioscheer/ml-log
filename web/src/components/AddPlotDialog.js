import React, { useState } from 'react';
import { withStyles } from '@material-ui/core/styles';
import {
    Button,
    Dialog,
    IconButton,
    Typography,
    TextField,
} from '@material-ui/core';
import MuiDialogTitle from '@material-ui/core/DialogTitle';
import MuiDialogContent from '@material-ui/core/DialogContent';
import MuiDialogActions from '@material-ui/core/DialogActions';
import CloseIcon from '@material-ui/icons/Close';

const styles = (theme) => ({
    root: {
        margin: 0,
        padding: theme.spacing(2),
    },
    closeButton: {
        position: 'absolute',
        right: theme.spacing(1),
        top: theme.spacing(1),
        color: theme.palette.grey[500],
    },
});

const DialogTitle = withStyles(styles)((props) => {
    const { children, classes, onClose, ...other } = props;
    return (
        <MuiDialogTitle disableTypography className={classes.root} {...other}>
            <Typography variant="h6">{children}</Typography>
            {onClose ? (
                <IconButton className={classes.closeButton} onClick={onClose}>
                    <CloseIcon />
                </IconButton>
            ) : null}
        </MuiDialogTitle>
    );
});

const DialogContent = withStyles((theme) => ({
    root: {
        padding: theme.spacing(2),
    },
}))(MuiDialogContent);

const DialogActions = withStyles((theme) => ({
    root: {
        margin: 0,
        padding: theme.spacing(1),
    },
}))(MuiDialogActions);

function AddPlotDialog({ open, handleClose, handleAdd }) {
    const [title, setTitle] = useState('');

    return (
        <div>
            <Dialog onClose={handleClose} open={open}>
                <DialogTitle onClose={handleClose}>Add plot</DialogTitle>
                <DialogContent dividers>
                    <TextField
                        label="Plot title"
                        variant="outlined"
                        value={title}
                        onChange={(e) => setTitle(e.target.value)}
                    />
                </DialogContent>
                <DialogActions>
                    <Button
                        autoFocus
                        onClick={() => {
                            handleAdd({ title });
                            handleClose();
                        }}
                        color="primary"
                    >
                        Add
                    </Button>
                </DialogActions>
            </Dialog>
        </div>
    );
}

export default AddPlotDialog;
